#include "PluginsProvider.hpp"

PluginsProvider::PluginsProvider(PluginTypesLocationsConfig &&confg)
    : definitions_providers_(std::move(confg.definitions_providers_dir())),
      sentences_providers_(std::move(confg.sentences_providers_dir())),
      images_providers_(std::move(confg.images_providers_dir())),
      audios_providers_(std::move(confg.audios_providers_dir())),
      format_processors_(std::move(confg.format_processors_dir())) {
}

auto PluginsProvider::get_definitions_provider(const std::string &name)
    -> std::optional<DefinitionsProviderWrapper> {
    return definitions_providers_.get(name);
}

auto PluginsProvider::get_sentences_provider(const std::string &name)
    -> std::optional<SentencesProviderWrapper> {
    return sentences_providers_.get(name);
}

auto PluginsProvider::get_audios_provider(const std::string &name)
    -> std::optional<AudiosProviderWrapper> {
    return audios_providers_.get(name);
}

auto PluginsProvider::get_images_provider(const std::string &name)
    -> std::optional<ImagesProviderWrapper> {
    return images_providers_.get(name);
}

auto PluginsProvider::get_format_processor(const std::string &name)
    -> std::optional<FormatProcessorWrapper> {
    return format_processors_.get(name);
}
