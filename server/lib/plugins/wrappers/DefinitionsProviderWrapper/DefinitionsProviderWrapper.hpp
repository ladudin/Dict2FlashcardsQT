#ifndef DEFINITIONS_PROVIDER_WRAPPER_H
#define DEFINITIONS_PROVIDER_WRAPPER_H

#include <cstdint>
#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

struct Card {
    Card()                                 = default;

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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Card,
                                   word,
                                   special,
                                   definition,
                                   examples,
                                   image_links,
                                   audio_links,
                                   tags,
                                   other);

class DefinitionsProviderWrapper : public BasePluginWrapper {
 public:
    using type = std::pair<std::vector<Card>, std::string>;

    explicit DefinitionsProviderWrapper(BasePluginWrapper &&base);

    auto get_dictionary_scheme()
        -> std::variant<nlohmann::json, PyExceptionInfo>;
    auto get(const std::string &word,
             const std::string &filter_query,
             uint64_t           batch_size,
             bool               restart)
        -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo>;

 private:
    std::unordered_map<std::string, std::optional<boost::python::object>>
        generators_;
};

static_assert(is_plugin_wrapper<DefinitionsProviderWrapper>);

#endif  // !DEFINITIONS_PROVIDER_WRAPPER_H
