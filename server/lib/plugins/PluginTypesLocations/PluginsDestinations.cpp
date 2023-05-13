#include "PluginsDestinations.hpp"

PluginsDestinations::PluginsDestinations(
    std::filesystem::path &&definitions_providers_dir,
    std::filesystem::path &&sentences_providers_dir,
    std::filesystem::path &&images_providers_dir,
    std::filesystem::path &&audios_providers_dir,
    std::filesystem::path &&format_processors_dir)
    : definitions_providers_dir_(std::move(definitions_providers_dir)),
      sentences_providers_dir_(std::move(sentences_providers_dir)),
      images_providers_dir_(std::move(images_providers_dir)),
      audios_providers_dir_(std::move(audios_providers_dir)),
      format_processors_dir_(std::move(format_processors_dir)) {
}
