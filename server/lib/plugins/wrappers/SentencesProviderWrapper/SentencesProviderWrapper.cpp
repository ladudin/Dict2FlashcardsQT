#include "SentencesProviderWrapper.hpp"

SentencesProviderWrapper::SentencesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto SentencesProviderWrapper::build(Container container)
    -> std::variant<SentencesProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(std::move(container));
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));
    return SentencesProviderWrapper(std::move(base));
}

auto SentencesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
