#include "SentencesProviderWrapper.hpp"

SentencesProviderWrapper::SentencesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto SentencesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
