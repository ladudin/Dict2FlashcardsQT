#include "response_generators.hpp"

#include <nlohmann/detail/exceptions.hpp>
#include <utility>

using nlohmann::json;

ResponceGenerator::ResponceGenerator() = default;

static auto return_error(const std::string &message) -> json {
    json dst;
    dst["status"]  = 1;
    dst["message"] = message;
    return dst;
}

auto ResponceGenerator::handle(const std::string &request) -> json {
    using std::string_literals::operator""s;
    json                        parsed_request;
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
    json json_query_type = parsed_request["query_type"];
    if (!json_query_type.is_string()) {
        return return_error("\"query_type\" field is has to be string");
    }
    std::string query_type = json_query_type;
    if (query_type == "init") {
        return handle_init(parsed_request);
    }
    if (query_type == "get_default_config") {
        return handle_get_default_config(parsed_request);
    }
    if (query_type == "get_config_scheme") {
        return handle_get_config_scheme(parsed_request);
    }
    if (query_type == "get_set_config") {
        return handle_set_config(parsed_request);
    }
    if (query_type == "list_plugins") {
        return handle_list_plugins(parsed_request);
    }
    if (query_type == "get_load_new_plugins") {
        return handle_load_new_plugins(parsed_request);
    }
    if (query_type == "get") {
        return handle_get(parsed_request);
    }
    if (query_type == "get_dict_scheme") {
        return handle_get_dict_scheme(parsed_request);
    }
    return return_error("Unknown query type: "s + query_type);
}
