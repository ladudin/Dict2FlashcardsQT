#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include "Container.hpp"
#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "spdlog/common.h"
#include <any>
#include <bits/ranges_algo.h>
#include <boost/python/import.hpp>
#include <concepts>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

// https://stackoverflow.com/a/71921982
template <class Dependent>
concept is_plugin =
    requires(Dependent c) { []<typename X>(IPluginWrapper<X> &) {}(c); };

template <typename Wrapper>
    requires std::derived_from<IPluginWrapper<std::any>, Wrapper> &&
             std::constructible_from<Wrapper, Container &&>
class IPluginsLoader {
 public:
    virtual ~IPluginsLoader() = default;

    virtual auto get(const std::string &plugin_name) -> std::optional<Wrapper>;
};

template <typename Wrapper>
    requires std::derived_from<IPluginWrapper<std::any>, Wrapper> &&
             std::constructible_from<Wrapper, Container &&>
class PluginsLoader : public IPluginsLoader<Wrapper> {
 public:
    explicit PluginsLoader(std::filesystem::path &&plugins_dir) noexcept(
        false) {
        try {
            boost::python::object sys = boost::python::import("sys");
            sys.attr("path").attr("append")(plugins_dir.c_str());
        } catch (...) {
            spdlog::throw_spdlog_ex("Couldn't import sys module");
        }

        std::ranges::for_each(
            std::filesystem::directory_iterator(plugins_dir),
            [this](const std::filesystem::path &dir_entry) {
                if (!std::filesystem::is_directory(dir_entry)) {
                    return;
                }
                auto module_name   = dir_entry.filename();
                auto loaded_module = boost::python::import(module_name.c_str());
                auto plugin_container =
                    Container::build(std::move(loaded_module));
                std::visit(
                    [this](Container &&container, std::string &&module_name) {
                        plugins_[module_name] = Wrapper(std::move(container));
                    },
                    [this](std::optional<PyExceptionInfo> &&exception_info,
                           std::string                    &&module_name) {
                        failed_plugins_[module_name] =
                            std::move(exception_info);
                    },
                    std::move(plugin_container),
                    std::move(module_name));
            });
    }

    auto get(const std::string &plugin_name)
        -> std::optional<Wrapper> override {
        auto res = plugins_.find(plugin_name);
        if (res == plugins_.end()) {
            return std::nullopt;
        }
        return *res;
    }

 private:
    std::unordered_map<std::string, Wrapper> plugins_;
    std::unordered_map<std::string, std::optional<PyExceptionInfo>>
        failed_plugins_;
};

#endif
