#ifndef PLUGINS_PROVIDER_H
#define PLUGINS_PROVIDER_H

#include "AudiosProviderWrapper.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "ImagesProviderWrapper.hpp"
#include "PluginTypesLocationsConfig.hpp"
#include "PluginsLoader.hpp"
#include "SentencesProviderWrapper.hpp"
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <utility>

class IPluginsProvider {
 public:
    virtual ~IPluginsProvider() = default;

    virtual auto get_definitions_provider(const std::string &name)
        -> std::optional<DefinitionsProviderWrapper>;

    virtual auto get_sentences_provider(const std::string &name)
        -> std::optional<SentencesProviderWrapper>;

    virtual auto get_images_provider(const std::string &name)
        -> std::optional<ImagesProviderWrapper>;

    virtual auto get_audios_provider(const std::string &name)
        -> std::optional<AudiosProviderWrapper>;

    virtual auto get_format_processor(const std::string &name)
        -> std::optional<FormatProcessorWrapper>;

    virtual auto reload_plugins() -> void;
};

class PluginsProvider : public IPluginsProvider {
 public:
    explicit PluginsProvider(PluginTypesLocationsConfig &&config);

    auto get_definitions_provider(const std::string &name)
        -> std::optional<DefinitionsProviderWrapper> override;

    auto get_sentences_provider(const std::string &name)
        -> std::optional<SentencesProviderWrapper> override;

    auto get_images_provider(const std::string &name)
        -> std::optional<ImagesProviderWrapper> override;

    auto get_audios_provider(const std::string &name)
        -> std::optional<AudiosProviderWrapper> override;

    auto get_format_processor(const std::string &name)
        -> std::optional<FormatProcessorWrapper> override;

    auto reload_plugins() -> void override;

 private:
    PluginsLoader<DefinitionsProviderWrapper> definitions_providers_;
    PluginsLoader<SentencesProviderWrapper>   sentences_providers_;
    PluginsLoader<ImagesProviderWrapper>      images_providers_;
    PluginsLoader<AudiosProviderWrapper>      audios_providers_;
    PluginsLoader<FormatProcessorWrapper>     format_processors_;
};

#endif  // !PLUGINS_PROVIDER_H
