#ifndef IMAGES_PROVIDER_WRAPPER_H
#define IMAGES_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class ImagesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    explicit ImagesProviderWrapper(Container container);

    void load() override;
    auto get(std::string word) -> provided_type override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json new_config) -> nlohmann::json override;
    void unload() override;

    ImagesProviderWrapper(const ImagesProviderWrapper &) = default;
    ImagesProviderWrapper(ImagesProviderWrapper &&)      = default;
    auto operator=(const ImagesProviderWrapper &)
        -> ImagesProviderWrapper & = default;
    auto operator=(ImagesProviderWrapper &&)
        -> ImagesProviderWrapper & = default;
};

#endif
