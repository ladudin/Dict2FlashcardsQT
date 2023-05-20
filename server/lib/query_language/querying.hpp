#ifndef QUERYING_H
#define QUERYING_H

#include <functional>
#include <nlohmann/json.hpp>
#include <optional>

auto prepare_filter(const std::string &query)
    -> std::function<std::optional<bool>(const nlohmann::json &json_card)>;

#endif  // !QUERYING_H
