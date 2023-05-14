#ifndef SENTENCES_PROVIDER_WRAPPER_H
#define SENTENCES_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"
#include <string>
#include <utility>
#include <vector>

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    explicit SentencesProviderWrapper(Container container);

    void load() override;
    auto get(std::string word) -> provided_type override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json new_config) -> nlohmann::json override;
    void unload() override;

    SentencesProviderWrapper(const SentencesProviderWrapper &) = default;
    SentencesProviderWrapper(SentencesProviderWrapper &&)      = default;
    auto operator=(const SentencesProviderWrapper &)
        -> SentencesProviderWrapper & = default;
    auto operator=(SentencesProviderWrapper &&)
        -> SentencesProviderWrapper & = default;
};

#endif
