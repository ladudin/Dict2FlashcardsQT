#include "ImagePluginWrapper.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <nlohmann/json.hpp>

using namespace nlohmann;

ImagePluginWrapper::ImagePluginWrapper(std::shared_ptr<IRequestable> connection)
    : BasicPluginWrapper(std::move(connection), "images") {
}

std::pair<Media, std::string> ImagePluginWrapper::get(const std::string &word,
                                                      size_t batch_size,
                                                      bool   restart) {
    json request_message = {
        {"query_type",  "get"       },
        {"plugin_type", plugin_type_},
        {"word",        word        },
        {"batch_size",  batch_size  },
        {"restart",     restart     }
    };
    std::pair<bool, std::string> response(
        connection_->request(request_message.dump()));
    if (!response.first)
        return {{}, "Server disconnected"};
    try {
        std::cout << response.second << std::endl;
        json response_message = json::parse(response.second);
        if (response_message.at("status").get<int>() != 0)
            return {{}, response_message.at("message").get<std::string>()};
        return {response_message.at("result").get<Media>(),
                response_message.at("message").get<std::string>()};
    } catch (...) {
        return {{}, "Wrong response format"};
    }
}
