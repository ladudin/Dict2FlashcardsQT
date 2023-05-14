#include "../include/wrappers/BasicPluginWrapper.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <nlohmann/json.hpp>

#include "containers/ExceptionInfo.h"

using namespace nlohmann;

BasicPluginWrapper::BasicPluginWrapper(std::shared_ptr<IRequestable> connection,
                                       std::string plugin_type)
    : connection_(std::move(connection)), plugin_type_(std::move(plugin_type)) {
}

Result<std::monostate>
BasicPluginWrapper::init(const std::string &plugin_name) {
    json request = {
        {"query_type",  "init"      },
        {"plugin_type", plugin_type_},
        {"plugin_name", plugin_name }
    };
    return std::visit(
        overload{[](std::string &&message) -> Result<std::monostate> {
                     try {
                         json response = json::parse(message);
                         if (response.at("status") != 0)
                             return Result<std::monostate>{
                                 ExceptionInfo{response.at("result").dump()}};
                     } catch (...) {
                         return Result<std::monostate>{
                             ExceptionInfo{"Wrong response format: "}};
                     }
                     return Result<std::monostate>{std::monostate{}};
                 },
                 [](ExceptionInfo &&exception_info) -> Result<std::monostate> {
                     return Result<std::monostate>{std::move(exception_info)};
                 }},
        connection_->request(request.dump()));
}

// std::string BasicPluginWrapper::get_default_config() {
//     json request = {
//         {"query_type",  "get_default_config"},
//         {"plugin_type", plugin_type_        }
//     };
//     std::string message = connection_->request(request.dump());
//     try {
//         json response = json::parse(message);
//         if (response.at("status") == 0)
//             return response.at("result").dump();
//         else
//             throw std::runtime_error(response.at("result"));
//     } catch (...) {
//         throw std::runtime_error("Wrong response format");
//     }
// }
//
// std::string BasicPluginWrapper::get_default_scheme() {
//     json request = {
//         {"query_type",  "get_default_scheme"},
//         {"plugin_type", plugin_type_        }
//     };
//     std::string message = connection_->request(request.dump());
//     try {
//         json response = json::parse(message);
//         if (response.at("status") == 0)
//             return response.at("result").dump();
//         else
//             throw std::runtime_error(response.at("result"));
//     } catch (...) {
//         throw std::runtime_error("Wrong response format");
//     }
// }
//
// std::map<std::string, std::string>
// BasicPluginWrapper::set_config(const std::string &new_config) {
//     json config;
//     try {
//         config = json::parse(new_config);
//     } catch (...) {
//         throw std::invalid_argument("Not a json");
//     }
//     json request = {
//         {"query_type",  "set_config"},
//         {"plugin_type", plugin_type_},
//         {"query",       config      }
//     };
//     std::string message = connection_->request(request.dump());
//     try {
//         json response = json::parse(message);
//         if (response.at("status") == 0)
//             return {};
//         else
//             return response.at("result")
//                 .get<std::map<std::string, std::string>>();
//     } catch (...) {
//         throw std::runtime_error("Wrong response format");
//     }
// }
//
// LoadResult BasicPluginWrapper::list_plugins() {
//     json request = {
//         {"query_type",  "list_plugins"},
//         {"plugin_type", plugin_type_  }
//     };
//     std::string message = connection_->request(request.dump());
//     try {
//         json response = json::parse(message);
//         if (response.at("status") == 0)
//             return LoadResult{response.at("result")
//                                   .at("success")
//                                   .get<std::vector<std::string>>(),
//                               response.at("result")
//                                   .at("failed")
//                                   .get<std::vector<std::string>>()};
//         else
//             throw std::runtime_error(response.at("result"));
//     } catch (...) {
//         throw std::runtime_error("Wrong response format");
//     }
// }
//
// LoadResult BasicPluginWrapper::load_new_plugins() {
//     json request = {
//         {"query_type",  "load_new_plugins"},
//         {"plugin_type", plugin_type_      }
//     };
//     std::string message = connection_->request(request.dump());
//     try {
//         json response = json::parse(message);
//         if (response.at("status") == 0)
//             return LoadResult{response.at("result")
//                                   .at("success")
//                                   .get<std::vector<std::string>>(),
//                               response.at("result")
//                                   .at("failed")
//                                   .get<std::vector<std::string>>()};
//         else
//             throw std::runtime_error(response.at("result"));
//     } catch (...) {
//         throw std::runtime_error("Wrong response format");
//     }
// }
