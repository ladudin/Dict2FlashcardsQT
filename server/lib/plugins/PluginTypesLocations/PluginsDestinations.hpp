#ifndef PLUGINS_DESTINATIONS_H
#define PLUGINS_DESTINATIONS_H

#include <filesystem>

class PluginsDestinations {
 public:
    PluginsDestinations(std::filesystem::path &&definitions_providers_dir,
                        std::filesystem::path &&sentences_providers_dir,
                        std::filesystem::path &&images_providers_dir,
                        std::filesystem::path &&audios_providers_dir,
                        std::filesystem::path &&format_processors_dir);

    [[nodiscard]] auto definitions_providers_dir() const
        -> std::filesystem::path;
    [[nodiscard]] auto sentences_providers_dir() const -> std::filesystem::path;
    [[nodiscard]] auto images_providers_dir() const -> std::filesystem::path;
    [[nodiscard]] auto audios_providers_dir() const -> std::filesystem::path;
    [[nodiscard]] auto format_processors_dir() const -> std::filesystem::path;

 private:
    std::filesystem::path definitions_providers_dir_;
    std::filesystem::path sentences_providers_dir_;
    std::filesystem::path images_providers_dir_;
    std::filesystem::path audios_providers_dir_;
    std::filesystem::path format_processors_dir_;
};

#endif  // !PLUGINS_DESTINATIONS_H
