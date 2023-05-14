#include "DefinitionsProviderWrapper.hpp"

DefinitionsProviderWrapper::DefinitionsProviderWrapper(Container container) {
}

auto DefinitionsProviderWrapper::get_dictionary_scheme() -> nlohmann::json {
    return {};
}

auto DefinitionsProviderWrapper::load() -> void {
}

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     uint64_t           batch_size) -> type {
    return {};
}

auto DefinitionsProviderWrapper::get_config_description() -> nlohmann::json {
    return {};
}

auto DefinitionsProviderWrapper::get_default_config() -> nlohmann::json {
    return {};
}

auto DefinitionsProviderWrapper::set_config(nlohmann::json &&new_config)
    -> nlohmann::json {
    return {};
}

auto DefinitionsProviderWrapper::unload() -> void {
}
