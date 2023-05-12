#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

struct Card {
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
    auto get_dictionary_scheme() -> nlohmann::json;
};
