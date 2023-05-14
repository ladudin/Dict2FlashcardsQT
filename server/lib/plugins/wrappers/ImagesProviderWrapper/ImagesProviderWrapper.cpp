#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(Container &&container)
    : container_(container) {
}

auto ImagesProviderWrapper::build(Container containter)
    -> std::variant<ImagesProviderWrapper, PyExceptionInfo> {
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> {
}

auto ImagesProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto ImagesProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto ImagesProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto ImagesProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto ImagesProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
