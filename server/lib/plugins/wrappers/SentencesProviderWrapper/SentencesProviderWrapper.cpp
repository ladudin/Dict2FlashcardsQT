#include "SentencesProviderWrapper.hpp"

SentencesProviderWrapper::SentencesProviderWrapper(Container container) {
}

auto SentencesProviderWrapper::load() -> void {
}

auto SentencesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> SentencesProviderWrapper::type {
    return {};
}

auto SentencesProviderWrapper::get_config_description() -> nlohmann::json {
    return {};
}

auto SentencesProviderWrapper::get_default_config() -> nlohmann::json {
    return {};
}

auto SentencesProviderWrapper::set_config(nlohmann::json &&new_config)
    -> nlohmann::json {
    return {};
}

auto SentencesProviderWrapper::unload() -> void {
}
