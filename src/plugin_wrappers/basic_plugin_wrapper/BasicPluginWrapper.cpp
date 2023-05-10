#include "BasicPluginWrapper.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace nlohmann;

BasicPluginWrapper::BasicPluginWrapper(std::shared_ptr<IRequestable> connection,
                                       std::string plugin_type)
    : connection_(std::move(connection)), plugin_type_(std::move(plugin_type)) {
}

void BasicPluginWrapper::init(std::string name) {
    json request = {
        {"query_type",  "init"      },
        {"plugin_type", plugin_type_},
        {"plugin_name", name        }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") != 0)
            throw std::runtime_error(response.at("result"));
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}

std::string BasicPluginWrapper::get_default_config() {
    json request = {
        {"query_type",  "get_default_config"},
        {"plugin_type", plugin_type_        }
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

std::string BasicPluginWrapper::get_default_scheme() {
    json request = {
        {"query_type",  "get_default_scheme"},
        {"plugin_type", plugin_type_        }
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

std::map<std::string, std::string>
BasicPluginWrapper::set_config(const std::string &new_config) {
    json config;
    try {
        config = json::parse(new_config);
    } catch (...) {
        throw std::invalid_argument("Not a json");
    }
    json request = {
        {"query_type",  "set_config"},
        {"plugin_type", plugin_type_},
        {"config",      config      }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return {};
        else
            return response.at("result")
                .get<std::map<std::string, std::string>>();
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}

LoadResult BasicPluginWrapper::list_plugins() {
    json request = {
        {"query_type",  "list_plugins"},
        {"plugin_type", plugin_type_  }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return LoadResult{response.at("result")
                                  .at("success")
                                  .get<std::vector<std::string>>(),
                              response.at("result")
                                  .at("failed")
                                  .get<std::vector<std::string>>()};
        else
            throw std::runtime_error(response.at("result"));
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}

LoadResult BasicPluginWrapper::load_new_plugins() {
    json request = {
        {"query_type",  "load_new_plugins"},
        {"plugin_type", plugin_type_      }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return LoadResult{response.at("result")
                                  .at("success")
                                  .get<std::vector<std::string>>(),
                              response.at("result")
                                  .at("failed")
                                  .get<std::vector<std::string>>()};
        else
            throw std::runtime_error(response.at("result"));
    } catch (...) {
        throw std::runtime_error("Wrong response format");
    }
}
