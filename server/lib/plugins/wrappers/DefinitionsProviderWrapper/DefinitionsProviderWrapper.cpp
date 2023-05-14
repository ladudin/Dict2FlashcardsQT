#include "DefinitionsProviderWrapper.hpp"

DefinitionsProviderWrapper::DefinitionsProviderWrapper(Container container) {
}

auto DefinitionsProviderWrapper::get_dictionary_scheme() -> nlohmann::json {
}

auto DefinitionsProviderWrapper::load() -> void {
}

auto DefinitionsProviderWrapper::get(std::string word) -> provided_type {
}

auto DefinitionsProviderWrapper::get_config_description() -> nlohmann::json {
}

auto DefinitionsProviderWrapper::get_default_config() -> nlohmann::json {
}

auto DefinitionsProviderWrapper::set_config(nlohmann::json new_config)
    -> nlohmann::json {
}

auto DefinitionsProviderWrapper::unload() -> void {
}
