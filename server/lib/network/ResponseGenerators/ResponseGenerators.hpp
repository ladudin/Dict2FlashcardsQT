#ifndef RESPONSE_GENERATORS_H
#define RESPONSE_GENERATORS_H

#include "PluginsBundle.hpp"
#include "PluginsProvider.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

class IResponceGenerator {
 public:
    virtual ~IResponceGenerator()                                     = default;
    virtual auto handle(const std::string &request) -> nlohmann::json = 0;

 private:
    virtual auto handle_init(const nlohmann::json &) -> nlohmann::json = 0;
    virtual auto handle_get_default_config(const nlohmann::json &)
        -> nlohmann::json = 0;
    virtual auto handle_get_config_scheme(const nlohmann::json &)
        -> nlohmann::json = 0;
    virtual auto handle_set_config(const nlohmann::json &)
        -> nlohmann::json = 0;
    virtual auto handle_list_plugins(const nlohmann::json &)
        -> nlohmann::json = 0;
    virtual auto handle_load_new_plugins(const nlohmann::json &)
        -> nlohmann::json                                             = 0;
    virtual auto handle_get(const nlohmann::json &) -> nlohmann::json = 0;
    virtual auto handle_get_dict_scheme(const nlohmann::json &)
        -> nlohmann::json = 0;
};

class ResponseGenerator : public IResponceGenerator {
 public:
    explicit ResponseGenerator(
        std::shared_ptr<PluginsProvider> plugins_provider);

    auto handle(const std::string &request) -> nlohmann::json override;

 private:
    static constexpr auto QUERY_TYPE_FIELD                = "batch_size";
    static constexpr auto PLUGIN_TYPE_FIELD               = "plugin_type";
    static constexpr auto CONFIG_FIELD                    = "config";
    static constexpr auto PLUGIN_NAME_FIELD               = "plugin_name";
    static constexpr auto FILTER_QUERY_FIELD              = "batch_size";
    static constexpr auto WORD_FIELD                      = "batch_size";
    static constexpr auto BATCH_SIZE_FIELD                = "batch_size";

    static constexpr auto DEFINITION_PROVIDER_PLUGIN_TYPE = "word";
    static constexpr auto SENTENCES_PROVIDER_PLUGIN_TYPE  = "sentences";
    static constexpr auto AUDIOS_PROVIDER_PLUGIN_TYPE     = "audios";
    static constexpr auto IMAGES_PROVIDER_PLUGIN_TYPE     = "images";
    static constexpr auto FORMAT_PROCESSOR_PLUGIN_TYPE    = "format";

    static constexpr auto INIT_QUERY_TYPE                 = "init";
    static constexpr auto LIST_PLUGINS_QUERY_TYPE         = "list_plugins";
    static constexpr auto GET_DEFAULT_CONFIG_QUERY_TYPE = "get_default_config";
    static constexpr auto GET_CONFIG_SCHEME_QUERY_TYPE  = "get_confit_scheme";
    static constexpr auto SET_CONFIG_QUERY_TYPE         = "set_config";
    static constexpr auto LOAD_NEW_PLUGINS_QUERY_TYPE   = "load_new_plugins";
    static constexpr auto GET_QUERY_TYPE                = "get";
    static constexpr auto GET_DICT_SCHEME_QUERY_TYPE    = "get_dict_scheme";

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
    PluginsBundle                          plugins_bundle_;
    const std::shared_ptr<PluginsProvider> plugins_provider_;
};

#endif  // !RESPONSE_GENERATORS_H
