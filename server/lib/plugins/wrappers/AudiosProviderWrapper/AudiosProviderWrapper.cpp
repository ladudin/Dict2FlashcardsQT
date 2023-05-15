#include "AudiosProviderWrapper.hpp"
#include "Container.hpp"
#include "PyExceptionInfo.hpp"
#include <cstdint>
#include <optional>
#include <utility>
#include <variant>

AudiosProviderWrapper::AudiosProviderWrapper(std::string &&name,
                                             Container   &&container)
    : name_(name), container_(container) {
}

auto AudiosProviderWrapper::build(std::string name, Container containter)
    -> std::variant<AudiosProviderWrapper, PyExceptionInfo> {
}

auto AudiosProviderWrapper::name() const -> const std::string & {
    return name_;
}

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo> {
}

auto AudiosProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto AudiosProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto AudiosProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto AudiosProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto AudiosProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
