#ifndef DEFINITIONS_PROVIDER_WRAPPER_H
#define DEFINITIONS_PROVIDER_WRAPPER_H

#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "Container.hpp"
#include "IPluginWrapper.hpp"
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
    : public IPluginWrapper<std::pair<std::vector<Card>, std::string>> {
 public:
    static auto build(std::string name, Container container)
        -> std::variant<DefinitionsProviderWrapper, PyExceptionInfo>;

    auto get_dictionary_scheme()
        -> std::variant<nlohmann::json, PyExceptionInfo>;
    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo>;
    [[nodiscard]] auto name() const -> const std::string & override;
    auto               load() -> std::optional<PyExceptionInfo> override;
    auto               unload() -> std::optional<PyExceptionInfo> override;
    auto               get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override;

 private:
    explicit DefinitionsProviderWrapper(std::string &&name,
                                        Container   &&container);

    std::string    name_;
    Container      container_;
    nlohmann::json config_;
};

static_assert(is_plugin_wrapper<DefinitionsProviderWrapper>);

#endif  // !DEFINITIONS_PROVIDER_WRAPPER_H
