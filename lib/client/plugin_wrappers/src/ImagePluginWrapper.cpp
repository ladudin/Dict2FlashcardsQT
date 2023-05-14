#include "../include/wrappers/ImagePluginWrapper.h"

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "exceptions/InvalidResponseFormatException.h"
#include "exceptions/ServerErrorException.h"

using namespace nlohmann;

ImagePluginWrapper::ImagePluginWrapper(std::shared_ptr<IRequestable> connection)
    : BasicPluginWrapper(std::move(connection), "image") {
}

std::vector<std::string> ImagePluginWrapper::get(const std::string &word,
                                                 size_t             count) {
    json request = {
        {"query_type",  "get"       },
        {"plugin_type", plugin_type_},
        {"word",        word        },
        {"count",       count       }
    };
    std::string message = connection_->request(request.dump());
    try {
        json response = json::parse(message);
        if (response.at("status") == 0)
            return response.at("result").get<std::vector<std::string>>();
        else
            throw ServerErrorException(response.at("result"));
    } catch (...) {
        throw InvalidResponseFormatException();
    }
}
