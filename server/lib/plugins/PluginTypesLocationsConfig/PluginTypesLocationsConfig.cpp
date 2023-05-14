#include "PluginTypesLocationsConfig.hpp"

PluginTypesLocationsConfig::PluginTypesLocationsConfig(
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

auto PluginTypesLocationsConfig::definitions_providers_dir() const
    -> std::filesystem::path {
    return definitions_providers_dir_;
}

auto PluginTypesLocationsConfig::sentences_providers_dir() const
    -> std::filesystem::path {
    return sentences_providers_dir_;
}

auto PluginTypesLocationsConfig::images_providers_dir() const
    -> std::filesystem::path {
    return images_providers_dir_;
}

auto PluginTypesLocationsConfig::audios_providers_dir() const
    -> std::filesystem::path {
    return audios_providers_dir_;
}

auto PluginTypesLocationsConfig::format_processors_dir() const
    -> std::filesystem::path {
    return format_processors_dir_;
}
