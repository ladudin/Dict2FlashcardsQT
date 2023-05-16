#ifndef PLUGIN_WRAPPER_INTERFACE_H
#define PLUGIN_WRAPPER_INTERFACE_H

#include "Container.hpp"
#include "PyExceptionInfo.hpp"
#include <concepts>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>

class IPluginWrapper {
 public:
    virtual ~IPluginWrapper()                                      = default;

    [[nodiscard]] virtual auto name() const -> const std::string & = 0;
    virtual auto               load() -> std::optional<PyExceptionInfo> = 0;
    virtual auto               get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> = 0;
    virtual auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> = 0;
    virtual auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json>    = 0;
    virtual auto unload() -> std::optional<PyExceptionInfo> = 0;
};

#endif  // !PLUGIN_WRAPPER_INTERFACE_H
