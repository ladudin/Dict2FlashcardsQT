#include "AudiosProviderWrapper.hpp"
#include <cstdint>

AudiosProviderWrapper::AudiosProviderWrapper(Container container) {
}

auto AudiosProviderWrapper::load() -> void {
}

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> AudiosProviderWrapper::type {
    return {};
}

auto AudiosProviderWrapper::get_config_description() -> nlohmann::json {
    return {};
}

auto AudiosProviderWrapper::get_default_config() -> nlohmann::json {
    return {};
}

auto AudiosProviderWrapper::set_config(nlohmann::json &&new_config)
    -> nlohmann::json {
    return {};
}

auto AudiosProviderWrapper::unload() -> void {
}
