#ifndef SENTENCES_PROVIDER_WRAPPER_H
#define SENTENCES_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    explicit SentencesProviderWrapper(Container container);

    auto get(const std::string &word, uint64_t batch_size)
        -> SentencesProviderWrapper::type;
    auto load() -> void override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json &&new_config) -> nlohmann::json override;
    auto unload() -> void override;

    SentencesProviderWrapper(const SentencesProviderWrapper &) = default;
    SentencesProviderWrapper(SentencesProviderWrapper &&)      = default;
    auto operator=(const SentencesProviderWrapper &)
        -> SentencesProviderWrapper & = default;
    auto operator=(SentencesProviderWrapper &&)
        -> SentencesProviderWrapper & = default;
};

#endif
