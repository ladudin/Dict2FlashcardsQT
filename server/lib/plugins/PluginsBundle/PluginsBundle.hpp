#ifndef PLUGINS_BUNDLE_H
#define PLUGINS_BUNDLE_H

#include "AudiosProviderWrapper.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "IPluginWrapper.hpp"
#include "ImagesProviderWrapper.hpp"
#include "SentencesProviderWrapper.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

class PluginsBundle {
 public:
    PluginsBundle();

    auto set_definitions_provider(DefinitionsProviderWrapper &&new_provider)
        -> void;

    auto set_sentences_provider(SentencesProviderWrapper &&new_provider)
        -> void;

    auto set_images_provider(ImagesProviderWrapper &&new_provider) -> void;

    auto set_audios_provider(AudiosProviderWrapper &&new_provider) -> void;

    auto set_format_processor(FormatProcessorWrapper &&new_provider) -> void;

    auto definitions_provider() -> std::optional<DefinitionsProviderWrapper> &;

    auto sentences_provider() -> std::optional<SentencesProviderWrapper> &;

    auto images_provider() -> std::optional<ImagesProviderWrapper> &;

    auto audios_provider() -> std::optional<AudiosProviderWrapper> &;

    auto format_processor() -> std::optional<FormatProcessorWrapper> &;

 private:
    std::optional<DefinitionsProviderWrapper> definitions_provider_ =
        std::nullopt;
    std::optional<SentencesProviderWrapper> sentences_provider_ = std::nullopt;
    std::optional<ImagesProviderWrapper>    images_provider_    = std::nullopt;
    std::optional<AudiosProviderWrapper>    audios_provider_    = std::nullopt;
    std::optional<FormatProcessorWrapper>   format_processor_   = std::nullopt;
};

#endif  // !PLUGINS_BUNDLE_H
