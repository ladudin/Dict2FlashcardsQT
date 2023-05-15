#include "wrappers/BasicPluginWrapper.h"

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <nlohmann/json.hpp>

#include "IRequestable.h"
#include "LoadResult.h"

using namespace nlohmann;

BasicPluginWrapper::BasicPluginWrapper(std::shared_ptr<IRequestable> connection,
                                       std::string plugin_type)
    : connection_(std::move(connection)), plugin_type_(std::move(plugin_type)) {
}

std::string BasicPluginWrapper::init(const std::string &plugin_name) {
    json request_message = {
        {"query_type",  "init"      },
        {"plugin_type", plugin_type_},
        {"plugin_name", plugin_name }
    };
    std::pair<bool, std::string> response(
        std::move(connection_->request(request_message.dump())));
    if (!response.first)
        return response.second;
    try {
        json response_message = json::parse(response.second);
        if (response_message.at("status") != 0)
            return response_message.at("error").dump();
        return {};
    } catch (...) {
        return "Wrong response format";
    }
}

std::pair<std::string, std::string> get_default_config() {
}

std::pair<std::string, std::string> get_default_scheme() {
}

std::pair<std::string, std::string> set_config(const std::string &new_config) {
}

std::pair<LoadResult, std::string> list_plugins() {
}

std::pair<LoadResult, std::string> load_new_plugins() {
}