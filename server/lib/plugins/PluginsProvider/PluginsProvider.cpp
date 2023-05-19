#include "PluginsProvider.hpp"
#include "AudiosProviderWrapper.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "IAudiosProviderWrapper.hpp"
#include "IDefinitionsProviderWrapper.hpp"
#include "IFormatProcessorWrapper.hpp"
#include "IImagesProviderWrapper.hpp"
#include "ISentencesProviderWrapper.hpp"
#include "ImagesProviderWrapper.hpp"
#include "pylifecycle.h"
#include "spdlog/common.h"

PluginsProvider::PluginsProvider(PluginTypesLocationsConfig &&confg)
    : definitions_providers_(
          std::make_unique<PluginsLoader<DefinitionsProviderWrapper,
                                         IDefinitionsProviderWrapper>>(
              std::move(confg.definitions_providers_dir))),
      sentences_providers_(
          std::make_unique<PluginsLoader<SentencesProviderWrapper,
                                         ISentencesProviderWrapper>>(
              std::move(confg.sentences_providers_dir))),
      images_providers_(
          std::make_unique<
              PluginsLoader<ImagesProviderWrapper, IImagesProviderWrapper>>(
              std::move(confg.images_providers_dir))),
      audios_providers_(
          std::make_unique<
              PluginsLoader<AudiosProviderWrapper, IAudiosProviderWrapper>>(
              std::move(confg.audios_providers_dir))),
      format_processors_(
          std::make_unique<
              PluginsLoader<FormatProcessorWrapper, IFormatProcessorWrapper>>(
              std::move(confg.format_processors_dir))) {
}

auto PluginsProvider::get_definitions_provider(const std::string &name)
    -> std::optional<std::variant<
        std::unique_ptr<DefinitionsProviderWrapper,
                        std::function<void(IDefinitionsProviderWrapper *)>>,
        PyExceptionInfo>> {
    return definitions_providers_->get(name);
}

auto PluginsProvider::get_sentences_provider(const std::string &name)
    -> std::optional<std::variant<
        std::unique_ptr<SentencesProviderWrapper,
                        std::function<void(ISentencesProviderWrapper *)>>,
        PyExceptionInfo>> {
    return sentences_providers_->get(name);
}

auto PluginsProvider::get_audios_provider(const std::string &name)
    -> std::optional<std::variant<
        std::unique_ptr<AudiosProviderWrapper,
                        std::function<void(IAudiosProviderWrapper *)>>,
        PyExceptionInfo>> {
    return audios_providers_->get(name);
}

auto PluginsProvider::get_images_provider(const std::string &name)
    -> std::optional<std::variant<
        std::unique_ptr<ImagesProviderWrapper,
                        std::function<void(IImagesProviderWrapper *)>>,
        PyExceptionInfo>> {
    return images_providers_->get(name);
}

auto PluginsProvider::get_format_processor(const std::string &name)
    -> std::optional<std::variant<
        std::unique_ptr<FormatProcessorWrapper,
                        std::function<void(IFormatProcessorWrapper *)>>,
        PyExceptionInfo>> {
    return format_processors_->get(name);
}

auto PluginsProvider::load_new_plugins() -> void {
    SPDLOG_THROW("load_new_plugins() is not implemented");
}
