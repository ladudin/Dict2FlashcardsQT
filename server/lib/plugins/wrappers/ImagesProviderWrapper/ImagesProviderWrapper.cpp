#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(Container container) {
}

auto ImagesProviderWrapper::load() -> void {
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> ImagesProviderWrapper::type {
    return {};
}

auto ImagesProviderWrapper::get_config_description() -> nlohmann::json {
    return {};
}

auto ImagesProviderWrapper::get_default_config() -> nlohmann::json {
    return {};
}

auto ImagesProviderWrapper::set_config(nlohmann::json &&new_config)
    -> nlohmann::json {
    return {};
}

auto ImagesProviderWrapper::unload() -> void {
}
