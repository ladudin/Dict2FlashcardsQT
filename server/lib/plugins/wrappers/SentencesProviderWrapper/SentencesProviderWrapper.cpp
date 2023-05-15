#include "SentencesProviderWrapper.hpp"
#include "Container.hpp"

SentencesProviderWrapper::SentencesProviderWrapper(std::string &&name,
                                                   Container   &&container)
    : name_(name), container_(container) {
}

auto SentencesProviderWrapper::build(std::string name, Container containter)
    -> std::variant<SentencesProviderWrapper, PyExceptionInfo> {
}

auto SentencesProviderWrapper::name() const -> const std::string & {
    return name_;
}

auto SentencesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo> {
}

auto SentencesProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto SentencesProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto SentencesProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto SentencesProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto SentencesProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
