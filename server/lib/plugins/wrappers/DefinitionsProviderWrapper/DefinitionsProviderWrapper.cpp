#include "DefinitionsProviderWrapper.hpp"

DefinitionsProviderWrapper::DefinitionsProviderWrapper(Container &&container)
    : container_(container) {
}

auto DefinitionsProviderWrapper::build(Container containter)
    -> std::variant<DefinitionsProviderWrapper, PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     uint64_t           batch_size)
    -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto DefinitionsProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto DefinitionsProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
