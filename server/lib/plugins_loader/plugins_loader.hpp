#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include "containers.hpp"
#include "spdlog/common.h"
#include <bits/ranges_algo.h>
#include <boost/python/import.hpp>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>

template <typename Wrapper>
class IPluginsLoader {
 public:
    virtual ~IPluginsLoader() = default;

    virtual auto get(const std::string &plugin_name) -> std::optional<Wrapper>;
};

template <typename Wrapper>
class PluginsLoader : public IPluginsLoader<Wrapper> {
 public:
    explicit PluginsLoader(std::filesystem::path &&plugins_dir) {
        try {
            boost::python::object sys = boost::python::import("sys");
            sys.attr("path").attr("append")(plugins_dir.c_str());
        } catch (...) {
            spdlog::throw_spdlog_ex("Couldn't import sys module");
        }

        std::ranges::for_each(
            std::filesystem::directory_iterator(plugins_dir),
            [](const std::filesystem::path &dir_entry) {
                if (!std::filesystem::is_directory(dir_entry)) {
                    return;
                }
                auto module_name   = dir_entry.filename();
                auto loaded_module = boost::python::import(module_name.c_str());
                auto plugin_container =
                    Container::build(std::move(loaded_module));
                std::visit(
                    [this, module_name](ExceptionInfo &&exception_info) {
                        failed_plugins_[module_name] = exception_info;
                    },
                    [this, module_name](Container &&container) {
                        plugins_[module_name] = Wrapper(container);
                    },
                    plugin_container);
            });
    }

    auto get(const std::string &plugin_name)
        -> std::optional<Wrapper> override {
    }

 private:
    std::unordered_map<std::string, Wrapper>       plugins_;
    std::unordered_map<std::string, ExceptionInfo> failed_plugins_;
};

#endif
