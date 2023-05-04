#ifndef PLUGINS_BUNDLE_H
#define PLUGINS_BUNDLE_H

#include "wrappers.hpp"
#include <optional>
#include <string>
#include <vector>

class PluginsBundle {
 public:
    // clang-format off
    auto get_definitions(std::string word)
        -> DefinitionsProviderWrapper::provided_type;

    auto get_sentences(std::string word)
        -> SentencesProviderWrapper::provided_type;

    auto get_images(std::string word)
        -> ImagesProviderWrapper::provided_type;

    auto get_audios(std::string word)
        -> AudiosProviderWrapper::provided_type;

    auto save_results(std::string word)
        -> FormatProcessorWrapper::provided_type;
    // clang-format on

    auto get_definitions_providers_config(JSON new_config) -> JSON;
    auto set_definitions_providers_config(JSON new_config) -> JSON;

    auto get_sentences_providers_config(JSON new_config) -> JSON;
    auto set_sentences_providers_config(JSON new_config) -> JSON;

    auto get_images_providers_config(JSON new_config) -> JSON;
    auto set_images_providers_config(JSON new_config) -> JSON;

    auto get_audios_providers_config(JSON new_config) -> JSON;
    auto set_audios_providers_config(JSON new_config) -> JSON;

    auto get_format_processors_config(JSON new_config) -> JSON;
    auto set_format_processors_config(JSON new_config) -> JSON;

 private:
    // std::optional<DefinitionsProviderWrapper> definitions_provider_ =
    //     std::nullopt;
    // std::optional<SentencesProviderWrapper> sentences_provider_ =
    // std::nullopt; std::optional<ImagesProviderWrapper>    images_provider_ =
    // std::nullopt; std::optional<AudiosProviderWrapper>    audios_provider_ =
    // std::nullopt; std::optional<FormatProcessorWrapper>   format_processor_
    // = std::nullopt;
};

#endif  // !PLUGINS_BUNDLE_H
