#ifndef PLUGIN_WRAPPER_INTERFACE_H
#define PLUGIN_WRAPPER_INTERFACE_H

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

    virtual ~IPluginWrapper()                                  = default;
    IPluginWrapper(const IPluginWrapper &)                     = delete;
    IPluginWrapper(IPluginWrapper &&) noexcept                 = default;
    auto operator=(const IPluginWrapper &) -> IPluginWrapper & = delete;
    auto operator=(IPluginWrapper &&) -> IPluginWrapper      & = delete;

 private:
    nlohmann::json config;
};

#endif  // !PLUGIN_WRAPPER_INTERFACE_H
