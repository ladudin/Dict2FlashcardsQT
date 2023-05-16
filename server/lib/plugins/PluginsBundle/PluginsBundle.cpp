#include "PluginsBundle.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include <cstddef>
#include <optional>

PluginsBundle::PluginsBundle() {
}

auto PluginsBundle::set_definitions_provider(
    DefinitionsProviderWrapper &&new_provider) -> void {
    definitions_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_sentences_provider(
    SentencesProviderWrapper &&new_provider) -> void {
    sentences_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_images_provider(ImagesProviderWrapper &&new_provider)
    -> void {
    images_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_audios_provider(AudiosProviderWrapper &&new_provider)
    -> void {
    audios_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_format_processor(FormatProcessorWrapper &&new_provider)
    -> void {
    format_processor_ = std::move(new_provider);
}

auto PluginsBundle::definitions_provider()
    -> std::optional<DefinitionsProviderWrapper> & {
    return definitions_provider_;
}

auto PluginsBundle::sentences_provider()
    -> std::optional<SentencesProviderWrapper> & {
    return sentences_provider_;
}

auto PluginsBundle::images_provider()
    -> std::optional<ImagesProviderWrapper> & {
    return images_provider_;
}

auto PluginsBundle::audios_provider()
    -> std::optional<AudiosProviderWrapper> & {
    return audios_provider_;
}

auto PluginsBundle::format_processor()
    -> std::optional<FormatProcessorWrapper> & {
    return format_processor_;
}
