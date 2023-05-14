#include "PluginsBundle.hpp"
#include <optional>

PluginsBundle::PluginsBundle() {
}

auto PluginsBundle::get_definitions(const std::string &word,
                                    uint64_t           batch_size)
    -> std::optional<DefinitionsProviderWrapper::type> {
    if (!definitions_provider_.has_value()) {
        return std::nullopt;
    }
    return definitions_provider_->get(word, batch_size);
}

auto PluginsBundle::get_sentences(const std::string &word, uint64_t batch_size)
    -> std::optional<SentencesProviderWrapper::type> {
}

auto PluginsBundle::get_images(const std::string &word, uint64_t batch_size)
    -> std::optional<ImagesProviderWrapper::type> {
}

auto PluginsBundle::get_audios(const std::string &word, uint64_t batch_size)
    -> std::optional<AudiosProviderWrapper::type> {
}

auto PluginsBundle::save_results(const std::string &word, uint64_t batch_size)
    -> std::optional<FormatProcessorWrapper::type> {
}

auto PluginsBundle::set_definitions_provider(DefinitionsProviderWrapper &&)
    -> void {
}

auto PluginsBundle::get_definitions_providers_config()
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_definitions_providers_config(
    nlohmann::json &&new_config) -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_sentences_provider(SentencesProviderWrapper &&)
    -> void {
}

auto PluginsBundle::get_sentences_providers_config()
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_sentences_providers_config(nlohmann::json &&new_config)
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_images_provider(ImagesProviderWrapper &&) -> void {
}

auto PluginsBundle::get_images_providers_config()
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_images_providers_config(nlohmann::json &&new_config)
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_audios_provider(AudiosProviderWrapper &&) -> void {
}

auto PluginsBundle::get_audios_providers_config()
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_audios_providers_config(nlohmann::json &&new_config)
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_format_processor(FormatProcessorWrapper &&) -> void {
}

auto PluginsBundle::get_format_processors_config()
    -> std::optional<nlohmann::json> {
}

auto PluginsBundle::set_format_processors_config(nlohmann::json &&new_config)
    -> std::optional<nlohmann::json> {
}
