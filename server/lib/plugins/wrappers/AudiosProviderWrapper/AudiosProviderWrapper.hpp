#ifndef AUDIOS_PROVIDER_WRAPPER_H
#define AUDIOS_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"
#include <string>
#include <utility>
#include <vector>

class AudiosProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    explicit AudiosProviderWrapper(Container container);

    void load() override;
    auto get(std::string word) -> provided_type override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json new_config) -> nlohmann::json override;
    void unload() override;

    AudiosProviderWrapper(const AudiosProviderWrapper &) = default;
    AudiosProviderWrapper(AudiosProviderWrapper &&)      = default;
    auto operator=(const AudiosProviderWrapper &)
        -> AudiosProviderWrapper & = default;
    auto operator=(AudiosProviderWrapper &&)
        -> AudiosProviderWrapper & = default;

 private:
    nlohmann::json config;
};

#endif  // !AUDIOS_PROVIDER_WRAPPER_H
