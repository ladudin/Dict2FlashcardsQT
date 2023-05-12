#ifndef PLUGINS_PROVIDER_H
#define PLUGINS_PROVIDER_H

#include "audios_provider_wrapper.hpp"
#include "definitions_provider_wrapper.hpp"
#include "format_processor_wrapper.hpp"
#include "images_provider_wrapper.hpp"
#include "sentences_provider_wrapper.hpp"
#include <optional>
#include <string>

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

class PluginsProvider : public IPluginsProvider {};

#endif  // !PLUGINS_PROVIDER_H
