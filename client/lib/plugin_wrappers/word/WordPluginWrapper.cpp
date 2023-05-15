#include "WordPluginWrapper.h"

#include <vector>

#include <nlohmann/json.hpp>

#include "Card.h"
#include "IRequestable.h"

using namespace nlohmann;

WordPluginWrapper::WordPluginWrapper(std::shared_ptr<IRequestable> connection)
    : BasicPluginWrapper(std::move(connection), "word") {
}

std::pair<std::vector<Card>, std::string>
WordPluginWrapper::get(const std::string &word,
                       const std::string &query_language,
                       size_t             batch_size,
                       bool               reload) {
    json request_message = {
        {"query_type",     "get_dict_scheme"},
        {"plugin_type",    plugin_type_     },
        {"query_language", query_language   },
        {"batch_size",     batch_size       },
        {"reload",         reload ? 1 : 0   }
    };
    std::pair<bool, std::string> response(
        std::move(connection_->request(request_message.dump())));
    if (!response.first)
        return std::make_pair(std::vector<Card>(), "Server disconnected");
    try {
        json response_message = json::parse(response.second);
        if (response_message.at("status").get<int>() != 0)
            return std::make_pair(std::vector<Card>(),
                                  response_message.at("error").get<std::string>());
        return std::make_pair(
            response_message.at("result").get<std::vector<Card>>(),
            std::string());
    } catch (...) {
        return std::make_pair(std::vector<Card>(), "Wrong response format");
    }
}

std::pair<std::string, std::string> WordPluginWrapper::get_dict_scheme() {
}