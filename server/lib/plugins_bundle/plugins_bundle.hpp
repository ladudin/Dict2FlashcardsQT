#ifndef PLUGINS_BUNDLE_H
#define PLUGINS_BUNDLE_H

#include "wrappers.hpp"
#include <optional>
#include <string>
#include <vector>

class PluginsBundle {
 public:
    PluginsBundle();
    auto get_definitions(std::string word)
        -> std::optional<DefinitionsProviderWrapper::provided_type>;

    auto get_sentences(std::string word)
        -> std::optional<SentencesProviderWrapper::provided_type>;

    auto get_images(std::string word)
        -> std::optional<ImagesProviderWrapper::provided_type>;

    auto get_audios(std::string word)
        -> std::optional<AudiosProviderWrapper::provided_type>;

    auto save_results(std::string word)
        -> std::optional<FormatProcessorWrapper::provided_type>;

    auto set_definitions_provider(DefinitionsProviderWrapper &&) -> void;
    auto get_definitions_providers_config() -> std::optional<nlohmann::json>;
    auto set_definitions_providers_config(nlohmann::json new_config)
        -> std::optional<nlohmann::json>;

    auto set_sentences_provider(SentencesProviderWrapper &&) -> void;
    auto get_sentences_providers_config() -> std::optional<nlohmann::json>;
    auto set_sentences_providers_config(nlohmann::json new_config)
        -> std::optional<nlohmann::json>;

    auto set_images_provider(ImagesProviderWrapper &&) -> void;
    auto get_images_providers_config() -> std::optional<nlohmann::json>;
    auto set_images_providers_config(nlohmann::json new_config)
        -> std::optional<nlohmann::json>;

    auto set_audios_provider(AudiosProviderWrapper &&) -> void;
    auto get_audios_providers_config() -> std::optional<nlohmann::json>;
    auto set_audios_providers_config(nlohmann::json new_config)
        -> std::optional<nlohmann::json>;

    auto set_format_processor(FormatProcessorWrapper &&) -> void;
    auto get_format_processors_config() -> std::optional<nlohmann::json>;
    auto set_format_processors_config(nlohmann::json new_config)
        -> std::optional<nlohmann::json>;

 private:
    std::optional<DefinitionsProviderWrapper> definitions_provider_ =
        std::nullopt;
    std::optional<SentencesProviderWrapper> sentences_provider_ = std::nullopt;
    std::optional<ImagesProviderWrapper>    images_provider_    = std::nullopt;
    std::optional<AudiosProviderWrapper>    audios_provider_    = std::nullopt;
    std::optional<FormatProcessorWrapper>   format_processor_   = std::nullopt;
};

#endif  // !PLUGINS_BUNDLE_H
