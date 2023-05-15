#ifndef PLUGINS_PROVIDER_H
#define PLUGINS_PROVIDER_H

#include "AudiosProviderWrapper.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "ImagesProviderWrapper.hpp"
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
        -> std::optional<
            std::variant<DefinitionsProviderWrapper, PyExceptionInfo>> = 0;

    virtual auto get_sentences_provider(const std::string &name)
        -> std::optional<
            std::variant<SentencesProviderWrapper, PyExceptionInfo>> = 0;

    virtual auto get_images_provider(const std::string &name) -> std::optional<
        std::variant<ImagesProviderWrapper, PyExceptionInfo>> = 0;

    virtual auto get_audios_provider(const std::string &name) -> std::optional<
        std::variant<AudiosProviderWrapper, PyExceptionInfo>> = 0;

    virtual auto get_format_processor(const std::string &name) -> std::optional<
        std::variant<FormatProcessorWrapper, PyExceptionInfo>> = 0;

    virtual auto load_new_plugins() -> void                    = 0;
};

struct PluginTypesLocationsConfig {
    std::filesystem::path definitions_providers_dir;
    std::filesystem::path sentences_providers_dir;
    std::filesystem::path images_providers_dir;
    std::filesystem::path audios_providers_dir;
    std::filesystem::path format_processors_dir;
};

class PluginsProvider : public IPluginsProvider {
 public:
    explicit PluginsProvider(PluginTypesLocationsConfig &&config);

    auto get_definitions_provider(const std::string &name) -> std::optional<
        std::variant<DefinitionsProviderWrapper, PyExceptionInfo>> override;

    auto get_sentences_provider(const std::string &name) -> std::optional<
        std::variant<SentencesProviderWrapper, PyExceptionInfo>> override;

    auto get_images_provider(const std::string &name) -> std::optional<
        std::variant<ImagesProviderWrapper, PyExceptionInfo>> override;

    auto get_audios_provider(const std::string &name) -> std::optional<
        std::variant<AudiosProviderWrapper, PyExceptionInfo>> override;

    auto get_format_processor(const std::string &name) -> std::optional<
        std::variant<FormatProcessorWrapper, PyExceptionInfo>> override;

    auto load_new_plugins() -> void override;

 private:
    PluginsLoader<DefinitionsProviderWrapper> definitions_providers_;
    PluginsLoader<SentencesProviderWrapper>   sentences_providers_;
    PluginsLoader<ImagesProviderWrapper>      images_providers_;
    PluginsLoader<AudiosProviderWrapper>      audios_providers_;
    PluginsLoader<FormatProcessorWrapper>     format_processors_;
};

#endif  // !PLUGINS_PROVIDER_H
