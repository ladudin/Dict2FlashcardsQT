#ifndef DEFINITIONS_PROVIDER_WRAPPER_H
#define DEFINITIONS_PROVIDER_WRAPPER_H

#include "Container.hpp"
#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

struct Card {
    Card(const Card &)                     = default;
    Card(Card &&)                          = default;
    auto operator=(const Card &) -> Card & = default;
    auto operator=(Card &&) -> Card      & = default;

 public:
    std::string              word;
    std::vector<std::string> special;
    std::string              definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    nlohmann::json           tags;
    nlohmann::json           other;
};

class DefinitionsProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<Card>, std::string>> {
 public:
    explicit DefinitionsProviderWrapper(Container container);

    auto get_dictionary_scheme() -> nlohmann::json;
    void load() override;
    auto get(std::string word) -> provided_type override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json new_config) -> nlohmann::json override;
    void unload() override;

    DefinitionsProviderWrapper(const DefinitionsProviderWrapper &) = default;
    DefinitionsProviderWrapper(DefinitionsProviderWrapper &&)      = default;
    auto operator=(const DefinitionsProviderWrapper &)
        -> DefinitionsProviderWrapper & = default;
    auto operator=(DefinitionsProviderWrapper &&)
        -> DefinitionsProviderWrapper & = default;

 private:
    nlohmann::json config;
};

#endif  // !DEFINITIONS_PROVIDER_WRAPPER_H
