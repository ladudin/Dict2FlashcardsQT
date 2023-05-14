#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include "Container.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "spdlog/common.h"
#include <bits/ranges_algo.h>
#include <boost/python/import.hpp>
#include <concepts>
#include <filesystem>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

template <typename Wrapper>
    requires implements_wrapper<Wrapper>
class IPluginsLoader {
 public:
    virtual ~IPluginsLoader() = default;

    virtual auto get(const std::string &plugin_name) -> std::optional<Wrapper>;
};

using Wrapper = DefinitionsProviderWrapper;

template <typename Wrapper>
    requires implements_wrapper<Wrapper>
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

                if (std::holds_alternative<std::optional<PyExceptionInfo>>(
                        plugin_container)) {
                    auto info = std::get<std::optional<PyExceptionInfo>>(
                        plugin_container);
                    failed_containers_.emplace(std::move(module_name),
                                               std::move(info));
                } else if (std::holds_alternative<Container>(
                               plugin_container)) {
                    auto container = std::get<Container>(plugin_container);
                    loaded_containers_.emplace(std::move(module_name),
                                               std::move(container));
                } else {
                    spdlog::throw_spdlog_ex(
                        "Unknown return from a container build");
                }
            });
    }

    auto get(const std::string &plugin_name)
        -> std::optional<Wrapper> override {
        auto res = loaded_containers_.find(plugin_name);
        if (res == loaded_containers_.end()) {
            return std::nullopt;
        }
        return Wrapper(res->second);
    }

 private:
    std::unordered_map<std::string, Container> loaded_containers_;
    std::unordered_map<std::string, std::optional<PyExceptionInfo>>
        failed_containers_;
};

#endif