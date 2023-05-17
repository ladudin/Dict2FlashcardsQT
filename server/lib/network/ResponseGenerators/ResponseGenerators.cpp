#include "ResponseGenerators.hpp"
#include "AudiosProviderWrapper.hpp"
#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "ImagesProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "SentencesProviderWrapper.hpp"
#include "spdlog/common.h"

#include <cstdint>
#include <nlohmann/detail/exceptions.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <utility>
#include <variant>

using nlohmann::json;
using std::string_literals::operator""s;

ResponseGenerator::ResponseGenerator(
    std::shared_ptr<PluginsProvider> plugins_provider)
    : plugins_provider_(std::move(plugins_provider)) {
}

static auto return_error(const std::string &message) -> json {
    json dst;
    dst["status"]  = 1;
    dst["message"] = message;
    return dst;
}

auto ResponseGenerator::handle(const std::string &request) -> json {
    json parsed_request;
    try {
        parsed_request = json::parse(request);
    } catch (json::exception &e) {
        return return_error(e.what());
    }
    if (!parsed_request.is_object()) {
        return return_error("Got non-json object as a request");
    }
    if (!parsed_request.contains("query_type")) {
        return return_error(
            "Every server request has to have \"query_type\" field");
    }
    json json_query_type = parsed_request[QUERY_TYPE_FIELD];
    if (!json_query_type.is_string()) {
        return return_error("\""s + QUERY_TYPE_FIELD +
                            "\" field is has to be a string");
    }
    std::string query_type = json_query_type;
    if (query_type == INIT_QUERY_TYPE) {
        return handle_init(parsed_request);
    }
    if (query_type == GET_DEFAULT_CONFIG_QUERY_TYPE) {
        return handle_get_default_config(parsed_request);
    }
    if (query_type == GET_CONFIG_SCHEME_QUERY_TYPE) {
        return handle_get_config_scheme(parsed_request);
    }
    if (query_type == SET_CONFIG_QUERY_TYPE) {
        return handle_set_config(parsed_request);
    }
    if (query_type == LIST_PLUGINS_QUERY_TYPE) {
        return handle_list_plugins(parsed_request);
    }
    if (query_type == LOAD_NEW_PLUGINS_QUERY_TYPE) {
        return handle_load_new_plugins(parsed_request);
    }
    if (query_type == GET_QUERY_TYPE) {
        return handle_get(parsed_request);
    }
    if (query_type == GET_DICT_SCHEME_QUERY_TYPE) {
        return handle_get_dict_scheme(parsed_request);
    }
    return return_error("Unknown query type: "s + query_type);
}

auto ResponseGenerator::handle_init(const nlohmann::json &request)
    -> nlohmann::json {
    if (!request.contains(PLUGIN_TYPE_FIELD)) {
        return return_error("\""s + PLUGIN_TYPE_FIELD +
                            "\" filed was not found in request");
    }
    if (!request[PLUGIN_TYPE_FIELD].is_string()) {
        return return_error("\""s + PLUGIN_TYPE_FIELD +
                            "\" field is expected to be a string");
    }
    auto plugin_type = request[PLUGIN_TYPE_FIELD].get<std::string>();

    if (!request.contains(PLUGIN_NAME_FIELD)) {
        return return_error("\""s + PLUGIN_NAME_FIELD +
                            "\" filed was not found in request");
    }
    if (!request[PLUGIN_NAME_FIELD].is_string()) {
        return return_error("\""s + PLUGIN_NAME_FIELD +
                            "\" field is expected to be a string");
    }
    auto plugin_name = request[PLUGIN_NAME_FIELD].get<std::string>();

    if (plugin_type == DEFINITION_PROVIDER_PLUGIN_TYPE) {
        auto requested_wrapper_option =
            plugins_provider_->get_definitions_provider(plugin_name);
        if (!requested_wrapper_option.has_value()) {
            return return_error("\"" + plugin_name +
                                "\" definition provider not found");
        }
        auto &wrapper_variant = requested_wrapper_option.value();
        if (std::holds_alternative<PyExceptionInfo>(wrapper_variant)) {
            auto exception_info = std::get<PyExceptionInfo>(wrapper_variant);

            return return_error("Exception was thrown during \"" + plugin_name +
                                "\" definitions provider's construction:\n" +
                                exception_info.stack_trace());
        }
        auto wrapper =
            std::move(std::get<DefinitionsProviderWrapper>(wrapper_variant));
        auto unique_wrapper =
            std::make_unique<DefinitionsProviderWrapper>(std::move(wrapper));
        plugins_bundle_.set_definitions_provider(std::move(unique_wrapper));
        return R"({"status": 0, "message": ""})"_json;
    }
    if (plugin_type == SENTENCES_PROVIDER_PLUGIN_TYPE) {
        auto requested_wrapper_option =
            plugins_provider_->get_sentences_provider(plugin_name);
        if (!requested_wrapper_option.has_value()) {
            return return_error("\"" + plugin_name +
                                "\" sentences provider not found");
        }
        auto &wrapper_variant = requested_wrapper_option.value();
        if (std::holds_alternative<PyExceptionInfo>(wrapper_variant)) {
            auto exception_info = std::get<PyExceptionInfo>(wrapper_variant);

            return return_error("Exception was thrown during \"" + plugin_name +
                                "\" sentence provider's construction:\n" +
                                exception_info.stack_trace());
        }
        auto wrapper = std::get<SentencesProviderWrapper>(wrapper_variant);
        auto unique_wrapper =
            std::make_unique<SentencesProviderWrapper>(std::move(wrapper));
        plugins_bundle_.set_sentences_provider(std::move(unique_wrapper));
        return R"({"status": 0, "message": ""})"_json;
    }
    if (plugin_type == IMAGES_PROVIDER_PLUGIN_TYPE) {
        auto requested_wrapper_option =
            plugins_provider_->get_images_provider(plugin_name);
        if (!requested_wrapper_option.has_value()) {
            return return_error("\"" + plugin_name +
                                "\" images provider not found");
        }
        auto &wrapper_variant = requested_wrapper_option.value();
        if (std::holds_alternative<PyExceptionInfo>(wrapper_variant)) {
            auto exception_info = std::get<PyExceptionInfo>(wrapper_variant);

            return return_error("Exception was thrown during \"" + plugin_name +
                                "\" images provider's construction:\n" +
                                exception_info.stack_trace());
        }
        auto wrapper = std::get<ImagesProviderWrapper>(wrapper_variant);
        auto unique_wrapper =
            std::make_unique<ImagesProviderWrapper>(std::move(wrapper));
        plugins_bundle_.set_images_provider(std::move(unique_wrapper));
        return R"({"status": 0, "message": ""})"_json;
    }
    if (plugin_type == AUDIOS_PROVIDER_PLUGIN_TYPE) {
        auto requested_wrapper_option =
            plugins_provider_->get_audios_provider(plugin_name);
        if (!requested_wrapper_option.has_value()) {
            return return_error("\"" + plugin_name +
                                "\" audios provider not found");
        }
        auto &wrapper_variant = requested_wrapper_option.value();
        if (std::holds_alternative<PyExceptionInfo>(wrapper_variant)) {
            auto exception_info = std::get<PyExceptionInfo>(wrapper_variant);

            return return_error("Exception was thrown during \"" + plugin_name +
                                "\" audios provider's construction:\n" +
                                exception_info.stack_trace());
        }
        auto wrapper = std::get<AudiosProviderWrapper>(wrapper_variant);
        auto unique_wrapper =
            std::make_unique<AudiosProviderWrapper>(std::move(wrapper));
        plugins_bundle_.set_audios_provider(std::move(unique_wrapper));
        return R"({"status": 0, "message": ""})"_json;
    }
    if (plugin_type == FORMAT_PROCESSOR_PLUGIN_TYPE) {
        auto requested_wrapper_option =
            plugins_provider_->get_format_processor(plugin_name);
        if (!requested_wrapper_option.has_value()) {
            return return_error("\"" + plugin_name +
                                "\" format processor not found");
        }
        auto &wrapper_variant = requested_wrapper_option.value();
        if (std::holds_alternative<PyExceptionInfo>(wrapper_variant)) {
            auto exception_info = std::get<PyExceptionInfo>(wrapper_variant);

            return return_error("Exception was thrown during \"" + plugin_name +
                                "\" format processor's construction:\n" +
                                exception_info.stack_trace());
        }
        auto wrapper = std::get<FormatProcessorWrapper>(wrapper_variant);
        auto unique_wrapper =
            std::make_unique<FormatProcessorWrapper>(std::move(wrapper));
        plugins_bundle_.set_format_processor(std::move(unique_wrapper));
        return R"({"status": 0, "message": ""})"_json;
    }
    return return_error("Unknown plugin_type: " + plugin_type);
}

auto ResponseGenerator::handle_get_default_config(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_get_default_config() is not implemented");
    return {};
}

auto ResponseGenerator::handle_get_config_scheme(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_get_config_scheme() is not implemented");
    return {};
}

auto ResponseGenerator::handle_set_config(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_set_config() is not implemented");
    return {};
}

auto ResponseGenerator::handle_list_plugins(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_list_plugins() is not implemented");
    return {};
}

auto ResponseGenerator::handle_load_new_plugins(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_load_new_plugins() is not implemented");
    return {};
}

auto ResponseGenerator::handle_get(const nlohmann::json &request)
    -> nlohmann::json {
    if (!request.contains(PLUGIN_TYPE_FIELD)) {
        return return_error("\""s + PLUGIN_TYPE_FIELD +
                            "\" filed was not found in request");
    }
    if (!request[PLUGIN_TYPE_FIELD].is_string()) {
        return return_error("\""s + PLUGIN_TYPE_FIELD +
                            "\" field is expected to be a string");
    }
    auto plugin_type = request[PLUGIN_TYPE_FIELD].get<std::string>();

    if (plugin_type == DEFINITION_PROVIDER_PLUGIN_TYPE) {
        auto *provider = plugins_bundle_.definitions_provider();
        if (provider == nullptr) {
            return return_error("Cannot return anything because definitions "
                                "provider is not initialized");
        }

        if (!request.contains(WORD_FIELD)) {
            return return_error("\""s + WORD_FIELD +
                                "\" filed was not found in request");
        }
        if (!request[WORD_FIELD].is_string()) {
            return return_error("\""s + WORD_FIELD +
                                "\" field is expected to be a string");
        }
        auto word = request[WORD_FIELD].get<std::string>();

        if (!request.contains(FILTER_QUERY_FIELD)) {
            return return_error("\""s + FILTER_QUERY_FIELD +
                                "\" fieled was not found in request");
        }
        if (!request[FILTER_QUERY_FIELD].is_string()) {
            return return_error("\""s + FILTER_QUERY_FIELD +
                                "\" field is expected to be a string");
        }
        auto filter_query = request[FILTER_QUERY_FIELD].get<std::string>();

        if (!request.contains(BATCH_SIZE_FIELD)) {
            return return_error("\""s + BATCH_SIZE_FIELD +
                                "\" filed was not found in request");
        }
        if (!request[BATCH_SIZE_FIELD].is_number()) {
            return return_error("\""s + BATCH_SIZE_FIELD +
                                "\" field is expected to be a number");
        }
        auto batch_size = request[BATCH_SIZE_FIELD].get<uint64_t>();

        if (!request.contains(RESTART_FIELD)) {
            return return_error("\""s + RESTART_FIELD +
                                "\" filed was not found in request");
        }
        if (!request[RESTART_FIELD].is_boolean()) {
            return return_error("\""s + RESTART_FIELD +
                                "\" field is expected to be a boolean");
        }
        auto restart = request[RESTART_FIELD].get<bool>();

        auto result_or_error =
            provider->get(word, filter_query, batch_size, restart);
        if (std::holds_alternative<PyExceptionInfo>(result_or_error)) {
            auto exception_info = std::get<PyExceptionInfo>(result_or_error);
            return return_error("Exception was thrown during \"" +
                                provider->name() + "\" definitions request:\n" +
                                exception_info.stack_trace());
        }
        if (std::holds_alternative<DefinitionsProviderWrapper::type>(
                result_or_error)) {
            auto result =
                std::get<DefinitionsProviderWrapper::type>(result_or_error);
            return result;
        }
        auto non_python_error_message = std::get<std::string>(result_or_error);

        auto json_message             = R"({"status": 1, "message": ")"s +
                            non_python_error_message + R"("})";
        return json::parse(json_message);
    }
    if (plugin_type == SENTENCES_PROVIDER_PLUGIN_TYPE) {
        return return_error(
            "Requests to sentences provider is not implemented");
    }
    if (plugin_type == IMAGES_PROVIDER_PLUGIN_TYPE) {
        return return_error("Requests to images provider is not implemented");
    }
    if (plugin_type == AUDIOS_PROVIDER_PLUGIN_TYPE) {
        return return_error("Requests to audios provider is not implemented");
    }
    if (plugin_type == FORMAT_PROCESSOR_PLUGIN_TYPE) {
        return return_error("Requests to format processor is not implemented");
    }
    return return_error("Unknown plugin type: "s + plugin_type);
}

auto ResponseGenerator::handle_get_dict_scheme(const nlohmann::json &request)
    -> nlohmann::json {
    spdlog::throw_spdlog_ex("handle_get_dict_scheme() is not implemented");
    return {};
}
