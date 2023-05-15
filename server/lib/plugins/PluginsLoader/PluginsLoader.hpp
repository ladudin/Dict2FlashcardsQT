#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include "BasePluginWrapper.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
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
            spdlog::throw_spdlog_ex("Couldn't import sys module");
        }

        std::ranges::for_each(
            std::filesystem::directory_iterator(plugins_dir),
            [this](const std::filesystem::path &dir_entry) {
                using std::string_literals::operator""s;

                spdlog::info("Loading plugin from "s + dir_entry.string());
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
                    spdlog::info("Failed to load plugin from "s +
                                 dir_entry.string());
                    failed_containers_.emplace(std::move(module_name),
                                               std::move(info));
                } else if (std::holds_alternative<Container>(
                               plugin_container)) {
                    auto container = std::get<Container>(plugin_container);
                    spdlog::info("Successfully loaded plugin from "s +
                                 dir_entry.string());
                    loaded_containers_.emplace(std::move(module_name),
                                               std::move(container));
                } else {
                    spdlog::throw_spdlog_ex(
                        "Unknown return from a container build");
                }
            });
    }

    auto get(const std::string &plugin_name)
        -> std::optional<std::variant<Wrapper, PyExceptionInfo>> override {
        using std::string_literals::operator""s;
        spdlog::info(plugin_name + " was requested");

        auto res = loaded_containers_.find(plugin_name);
        if (res == loaded_containers_.end()) {
            spdlog::info(plugin_name + " not found");
            return std::nullopt;
        }
        spdlog::info(plugin_name + " was found");
        auto wrapper_or_error = Wrapper::build(plugin_name, res->second);
        if (std::holds_alternative<BasePluginWrapper<typename Wrapper::type>>(
                wrapper_or_error)) {
            auto base_wrapper =
                std::get<BasePluginWrapper<typename Wrapper::type>>(
                    wrapper_or_error);
            auto after_cast = *static_cast<Wrapper *>(&base_wrapper);
            return after_cast;
        }
        return std::nullopt;
    }

    auto load_new_plugins() -> void override {
        throw std::runtime_error("load_new_plugins() is not implemented");
    }

 private:
    std::unordered_map<std::string, Container> loaded_containers_;
    std::unordered_map<std::string, std::optional<PyExceptionInfo>>
        failed_containers_;
};

#endif
