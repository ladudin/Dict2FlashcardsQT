#include "PluginsProvider.hpp"
#include "pylifecycle.h"
#include "spdlog/common.h"

PluginsProvider::PluginsProvider(PluginTypesLocationsConfig &&confg)
    : definitions_providers_(std::move(confg.definitions_providers_dir())),
      sentences_providers_(std::move(confg.sentences_providers_dir())),
      images_providers_(std::move(confg.images_providers_dir())),
      audios_providers_(std::move(confg.audios_providers_dir())),
      format_processors_(std::move(confg.format_processors_dir())) {
}

auto PluginsProvider::get_definitions_provider(const std::string &name)
    -> std::optional<
        std::variant<DefinitionsProviderWrapper, PyExceptionInfo>> {
    return definitions_providers_.get(name);
}

auto PluginsProvider::get_sentences_provider(const std::string &name)
    -> std::optional<std::variant<SentencesProviderWrapper, PyExceptionInfo>> {
    return sentences_providers_.get(name);
}

auto PluginsProvider::get_audios_provider(const std::string &name)
    -> std::optional<std::variant<AudiosProviderWrapper, PyExceptionInfo>> {
    return audios_providers_.get(name);
}

auto PluginsProvider::get_images_provider(const std::string &name)
    -> std::optional<std::variant<ImagesProviderWrapper, PyExceptionInfo>> {
    return images_providers_.get(name);
}

auto PluginsProvider::get_format_processor(const std::string &name)
    -> std::optional<std::variant<FormatProcessorWrapper, PyExceptionInfo>> {
    return format_processors_.get(name);
}

auto PluginsProvider::load_new_plugins() -> void {
    spdlog::throw_spdlog_ex("load_new_plugins() is not implemented");
}
