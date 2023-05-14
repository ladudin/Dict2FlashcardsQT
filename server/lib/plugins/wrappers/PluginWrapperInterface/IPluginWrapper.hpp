#ifndef PLUGIN_WRAPPER_INTERFACE_H
#define PLUGIN_WRAPPER_INTERFACE_H

#include "Container.hpp"
#include <concepts>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

template <class T>
class IPluginWrapper {
 public:
    using provided_type = T;

    virtual void load();
    virtual auto get(std::string word) -> T;
    virtual auto get_config_description() -> nlohmann::json;
    virtual auto get_default_config() -> nlohmann::json;
    virtual auto set_config(nlohmann::json new_config) -> nlohmann::json;
    virtual void unload();

    virtual ~IPluginWrapper() = default;
};

template <class Dependent>
concept implements_wrapper =
    requires(Dependent c) { []<typename X>(IPluginWrapper<X> &) {}(c); } &&
    std::constructible_from<Dependent, Container> &&
    std::copy_constructible<Dependent>;

// constexpr bool test = ;

#endif  // !PLUGIN_WRAPPER_INTERFACE_H
