#ifndef RESPONSE_GENERATORS_H
#define RESPONSE_GENERATORS_H

#include "plugins_bundle.hpp"
#include "plugins_provider.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

class IResponceGenerator {
 public:
    virtual ~IResponceGenerator() = default;
    virtual auto handle(const std::string &request) -> nlohmann::json;

 protected:
    virtual auto handle_init(const nlohmann::json &) -> nlohmann::json;
    virtual auto handle_get_default_config(const nlohmann::json &)
        -> nlohmann::json;
    virtual auto handle_get_config_scheme(const nlohmann::json &)
        -> nlohmann::json;
    virtual auto handle_set_config(const nlohmann::json &) -> nlohmann::json;
    virtual auto handle_list_plugins(const nlohmann::json &) -> nlohmann::json;
    virtual auto handle_load_new_plugins(const nlohmann::json &)
        -> nlohmann::json;
    virtual auto handle_get(const nlohmann::json &) -> nlohmann::json;
    virtual auto handle_get_dict_scheme(const nlohmann::json &)
        -> nlohmann::json;
};

// Где-то хранить state между сообщениями. Энивей многошаговый запрос
// разрешается через handle()
class ResponceGenerator : public IResponceGenerator {
 public:
    ResponceGenerator();

    auto handle(const std::string &request) -> nlohmann::json override;

 protected:
    auto handle_init(const nlohmann::json &request) -> nlohmann::json override;
    auto handle_get_default_config(const nlohmann::json &request)
        -> nlohmann::json override;
    auto handle_get_config_scheme(const nlohmann::json &request)
        -> nlohmann::json override;
    auto handle_set_config(const nlohmann::json &request)
        -> nlohmann::json override;
    auto handle_list_plugins(const nlohmann::json &request)
        -> nlohmann::json override;
    auto handle_load_new_plugins(const nlohmann::json &request)
        -> nlohmann::json override;
    auto handle_get(const nlohmann::json &request) -> nlohmann::json override;
    auto handle_get_dict_scheme(const nlohmann::json &request)
        -> nlohmann::json override;

 private:
    PluginsBundle                          bundle_;
    const std::shared_ptr<PluginsProvider> plugins_provider_;
};

#endif  // !RESPONSE_GENERATORS_H
