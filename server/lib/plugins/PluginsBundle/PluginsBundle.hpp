#ifndef PLUGINS_BUNDLE_H
#define PLUGINS_BUNDLE_H

#include "IAudiosProviderWrapper.hpp"
#include "IDefinitionsProviderWrapper.hpp"
#include "IFormatProcessorWrapper.hpp"
#include "IImagesProviderWrapper.hpp"
#include "ISentencesProviderWrapper.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

class PluginsBundle {
 public:
    PluginsBundle();

    auto set_definitions_provider(
        std::unique_ptr<IDefinitionsProviderWrapper> &&new_provider) -> void;

    auto set_sentences_provider(
        std::unique_ptr<ISentencesProviderWrapper> &&new_provider) -> void;

    auto
    set_images_provider(std::unique_ptr<IImagesProviderWrapper> &&new_provider)
        -> void;

    auto
    set_audios_provider(std::unique_ptr<IAudiosProviderWrapper> &&new_provider)
        -> void;

    auto set_format_processor(
        std::unique_ptr<IFormatProcessorWrapper> &&new_provider) -> void;

    auto definitions_provider() -> const IDefinitionsProviderWrapper *;

    auto sentences_provider() -> const ISentencesProviderWrapper *;

    auto images_provider() -> const IImagesProviderWrapper *;

    auto audios_provider() -> const IAudiosProviderWrapper *;

    auto format_processor() -> const IFormatProcessorWrapper *;

 private:
    std::unique_ptr<IDefinitionsProviderWrapper> definitions_provider_ =
        nullptr;
    std::unique_ptr<ISentencesProviderWrapper> sentences_provider_ = nullptr;
    std::unique_ptr<IImagesProviderWrapper>    images_provider_    = nullptr;
    std::unique_ptr<IAudiosProviderWrapper>    audios_provider_    = nullptr;
    std::unique_ptr<IFormatProcessorWrapper>   format_processor_   = nullptr;
};

#endif  // !PLUGINS_BUNDLE_H
