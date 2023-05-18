#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <boost/python/errors.hpp>
#include <boost/python/import.hpp>
#include <complex>
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

#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

template <typename Wrapper>
    requires is_plugin_wrapper<Wrapper>
class IPluginsLoader {
 public:
    virtual ~IPluginsLoader() = default;

    virtual auto get(const std::string &plugin_name)
        -> std::optional<std::variant<Wrapper, PyExceptionInfo>> = 0;
    virtual auto load_new_plugins() -> void                      = 0;
};

// #include "DefinitionsProviderWrapper.hpp"
// using Wrapper = DefinitionsProviderWrapper;

template <typename Wrapper>
    requires is_plugin_wrapper<Wrapper>
class PluginsLoader : public IPluginsLoader<Wrapper> {
 public:
    explicit PluginsLoader(std::filesystem::path &&plugins_dir) noexcept(
        false) {
        try {
            boost::python::object sys = boost::python::import("sys");
            sys.attr("path").attr("append")(plugins_dir.c_str());
        } catch (const boost::python::error_already_set &) {
            SPDLOG_THROW("Couldn't import sys module");
        }

        std::ranges::for_each(
            std::filesystem::directory_iterator(plugins_dir),
            [this](const std::filesystem::path &dir_entry) {
                using std::string_literals::operator""s;
                SPDLOG_INFO("Loading plugin from "s + dir_entry.string());

                if (!std::filesystem::is_directory(dir_entry)) {
                    return;
                }

                auto                  module_name = dir_entry.filename();
                boost::python::object loaded_module;
                try {
                    loaded_module = boost::python::import(module_name.c_str());
                } catch (const boost::python::error_already_set &) {
                    SPDLOG_INFO("Failed to import module: "s +
                                module_name.string());
                    auto error_info = PyExceptionInfo::build();
                    failed_containers_.emplace(std::move(module_name),
                                               std::move(error_info));
                    return;
                }

                auto wrapper_or_error =
                    Wrapper::build(module_name.string(), loaded_module);

                SPDLOG_INFO("Successfully imported Python module: "s +
                            module_name.string());

                if (std::holds_alternative<PyExceptionInfo>(wrapper_or_error)) {
                    auto info = std::get<PyExceptionInfo>(wrapper_or_error);
                    SPDLOG_INFO("Failed to load plugin from "s +
                                dir_entry.string());
                    failed_containers_.emplace(std::move(module_name),
                                               std::move(info));
                } else if (std::holds_alternative<Wrapper>(wrapper_or_error)) {
                    auto wrapper =
                        std::move(std::get<Wrapper>(wrapper_or_error));
                    SPDLOG_INFO("Successfully loaded plugin from "s +
                                dir_entry.string());
                    loaded_containers_.emplace(std::move(module_name),
                                               std::move(wrapper));
                } else {
                    SPDLOG_THROW("Unknown return from a container build");
                }
            });
    }

    auto get(const std::string &plugin_name)
        -> std::optional<std::variant<Wrapper, PyExceptionInfo>> override {
        using std::string_literals::operator""s;
        SPDLOG_INFO(plugin_name + " was requested");

        auto res = loaded_containers_.find(plugin_name);
        if (res == loaded_containers_.end()) {
            SPDLOG_INFO(plugin_name + " not found");
            return std::nullopt;
        }
        SPDLOG_INFO(plugin_name + " was found");
        auto found_wrapper = res->second;
        return found_wrapper;
    }

    auto load_new_plugins() -> void override {
        throw std::runtime_error("load_new_plugins() is not implemented");
    }

 private:
    std::unordered_map<std::string, Wrapper> loaded_containers_;
    std::unordered_map<std::string, std::optional<PyExceptionInfo>>
        failed_containers_;
};

#endif
