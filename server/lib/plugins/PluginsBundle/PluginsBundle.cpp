#include "PluginsBundle.hpp"
#include "PyExceptionInfo.hpp"
#include <optional>

PluginsBundle::PluginsBundle() {
}

auto PluginsBundle::get_definitions(const std::string &word,
                                    uint64_t           batch_size)
    -> std::optional<
        std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo>> {
    if (!definitions_provider_.has_value()) {
        return std::nullopt;
    }
    return definitions_provider_->get(word, batch_size);
}

auto PluginsBundle::get_sentences(const std::string &word, uint64_t batch_size)
    -> std::optional<
        std::variant<SentencesProviderWrapper::type, PyExceptionInfo>> {
    if (!sentences_provider_.has_value()) {
        return std::nullopt;
    }
    return sentences_provider_->get(word, batch_size);
}

auto PluginsBundle::get_images(const std::string &word, uint64_t batch_size)
    -> std::optional<
        std::variant<ImagesProviderWrapper::type, PyExceptionInfo>> {
    if (!images_provider_.has_value()) {
        return std::nullopt;
    }
    return images_provider_->get(word, batch_size);
}

auto PluginsBundle::get_audios(const std::string &word, uint64_t batch_size)
    -> std::optional<
        std::variant<AudiosProviderWrapper::type, PyExceptionInfo>> {
    if (!audios_provider_.has_value()) {
        return std::nullopt;
    }
    return audios_provider_->get(word, batch_size);
}

auto PluginsBundle::save_results(ResultFilesPaths &&paths) -> std::optional<
    std::variant<FormatProcessorWrapper::type, PyExceptionInfo>> {
    if (!format_processor_.has_value()) {
        return std::nullopt;
    }
    return format_processor_->get(std::move(paths));
}

auto PluginsBundle::set_definitions_provider(
    DefinitionsProviderWrapper &&new_provider) -> void {
    definitions_provider_ = std::move(new_provider);
}

auto PluginsBundle::get_definitions_providers_config()
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!definitions_provider_.has_value()) {
        return std::nullopt;
    }
    return definitions_provider_->get_default_config();
}

auto PluginsBundle::set_definitions_providers_config(
    nlohmann::json &&new_config)
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!definitions_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_sentences_provider(SentencesProviderWrapper &&)
    -> void {
}

auto PluginsBundle::get_sentences_providers_config()
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!sentences_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_sentences_providers_config(nlohmann::json &&new_config)
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!sentences_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_images_provider(ImagesProviderWrapper &&) -> void {
}

auto PluginsBundle::get_images_providers_config()
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!images_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_images_providers_config(nlohmann::json &&new_config)
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!images_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_audios_provider(AudiosProviderWrapper &&) -> void {
}

auto PluginsBundle::get_audios_providers_config()
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!audios_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_audios_providers_config(nlohmann::json &&new_config)
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!audios_provider_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_format_processor(FormatProcessorWrapper &&) -> void {
}

auto PluginsBundle::get_format_processors_config()
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!format_processor_.has_value()) {
        return std::nullopt;
    }
}

auto PluginsBundle::set_format_processors_config(nlohmann::json &&new_config)
    -> std::optional<std::variant<PyExceptionInfo, nlohmann::json>> {
    if (!format_processor_.has_value()) {
        return std::nullopt;
    }
}
