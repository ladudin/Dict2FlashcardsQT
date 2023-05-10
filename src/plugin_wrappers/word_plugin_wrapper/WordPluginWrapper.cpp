#include "WordPluginWrapper.h"

#include <vector>

#include "containers/Card.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;

WordPluginWrapper::WordPluginWrapper(std::shared_ptr<IRequestable> connection)
    : BasicPluginWrapper(std::move(connection), "word") {
}

std::string WordPluginWrapper::get_dict_scheme() {
    json request = {
        {"query_type",  "get_dict_scheme"},
        {"plugin_type", plugin_type_     }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return response.at("result").dump();
        else
            throw std::runtime_error(response.at("result"));
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}

std::vector<Card> WordPluginWrapper::get(const std::string &word) {
    json request = {
        {"query_type",  "get"       },
        {"plugin_type", plugin_type_},
        {"query",       word        }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return response.at("result").get<std::vector<Card>>();
        else
            throw std::runtime_error(response.at("result"));
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}