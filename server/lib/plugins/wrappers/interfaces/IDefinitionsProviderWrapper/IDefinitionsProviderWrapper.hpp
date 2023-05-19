#ifndef I_DEFINITIONS_PROVIDER_WRAPPER_H
#define I_DEFINITIONS_PROVIDER_WRAPPER_H

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "IPluginWrapper.hpp"

struct SourceWithAdditionalInfo {
    std::string src;
    std::string info;
};

inline void to_json(nlohmann ::json                &nlohmann_json_j,
                    const SourceWithAdditionalInfo &nlohmann_json_t) {
    nlohmann_json_j = {nlohmann_json_t.src, nlohmann_json_t.info};
}

inline void from_json(const nlohmann ::json    &nlohmann_json_j,
                      SourceWithAdditionalInfo &nlohmann_json_t) {
    nlohmann_json_j.at(0).get_to(nlohmann_json_t.src);
    nlohmann_json_j.at(1).get_to(nlohmann_json_t.info);
}

struct Media {
    std::vector<SourceWithAdditionalInfo> local;
    std::vector<SourceWithAdditionalInfo> web;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Media, local, web);

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
    Media                    audios;
    Media                    images;
    nlohmann::json           tags;
    nlohmann::json           other;
};

// TODO(blackdeer): solve optional keys

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Card,
                                   word,
                                   special,
                                   definition,
                                   examples,
                                   images,
                                   audios,
                                   tags,
                                   other);

class IDefinitionsProviderWrapper : public virtual IPluginWrapper {
 public:
    using type = std::pair<std::vector<Card>, std::string>;

    virtual auto get_dictionary_scheme()
        -> std::variant<nlohmann::json, PyExceptionInfo> = 0;

    virtual auto get(const std::string &word,
                     const std::string &filter_query,
                     uint64_t           batch_size,
                     bool               restart)
        -> std::variant<type, std::string, PyExceptionInfo> = 0;
};

#endif
