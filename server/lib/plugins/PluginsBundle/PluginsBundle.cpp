#include "PluginsBundle.hpp"
#include "PyExceptionInfo.hpp"
#include <cstddef>
#include <optional>

PluginsBundle::PluginsBundle() = default;

auto PluginsBundle::set_definitions_provider(
    std::unique_ptr<IDefinitionsProviderWrapper> &&new_provider) -> void {
    definitions_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_sentences_provider(
    std::unique_ptr<ISentencesProviderWrapper> &&new_provider) -> void {
    sentences_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_images_provider(
    std::unique_ptr<IImagesProviderWrapper> &&new_provider) -> void {
    images_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_audios_provider(
    std::unique_ptr<IAudiosProviderWrapper> &&new_provider) -> void {
    audios_provider_ = std::move(new_provider);
}

auto PluginsBundle::set_format_processor(
    std::unique_ptr<IFormatProcessorWrapper> &&new_provider) -> void {
    format_processor_ = std::move(new_provider);
}

auto PluginsBundle::definitions_provider()
    -> const IDefinitionsProviderWrapper * {
    return definitions_provider_.get();
}

auto PluginsBundle::sentences_provider() -> const ISentencesProviderWrapper * {
    return sentences_provider_.get();
}

auto PluginsBundle::images_provider() -> const IImagesProviderWrapper * {
    return images_provider_.get();
}

auto PluginsBundle::audios_provider() -> const IAudiosProviderWrapper * {
    return audios_provider_.get();
}

auto PluginsBundle::format_processor() -> const IFormatProcessorWrapper * {
    return format_processor_.get();
}
