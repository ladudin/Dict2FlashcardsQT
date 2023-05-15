#ifndef DEFINITIONS_PROVIDER_WRAPPER_H
#define DEFINITIONS_PROVIDER_WRAPPER_H

#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

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
    : public BasePluginWrapper<std::pair<std::vector<Card>, std::string>> {
 public:
    auto get_dictionary_scheme()
        -> std::variant<nlohmann::json, PyExceptionInfo>;
    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo>;
};

static_assert(is_plugin_wrapper<DefinitionsProviderWrapper>);

#endif  // !DEFINITIONS_PROVIDER_WRAPPER_H
