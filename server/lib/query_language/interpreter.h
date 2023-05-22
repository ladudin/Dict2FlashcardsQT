#pragma once
#include "parcer.h"

class interpreter : expr_visitor {
 public:
    interpreter();
    value interpret(expr *expression, nlohmann::json card_);

 private:
    nlohmann::json card;
    value          result;
    auto           evaluate(expr *expression) -> value;
    auto           is_truthy(value val) -> bool;
    auto           is_equal(value left, value right) -> bool;
    void           visit(binary *expr) override;
    void           visit(grouping *expr) override;
    void           visit(unary *expr) override;
    void           visit(literal *expr) override;
    void           visit(func_in *expr) override;
    void           visit(logical_expr *ex) override;
    auto find_word_inJson(std::string word, nlohmann::json jsonValue) -> bool;
    void check_number_operand(token oper, value operand);
    void check_number_operands(token oper, value left, value right);
    auto find_json_value(const nlohmann::json &card, std::vector<std::string>)
        -> nlohmann::json;
    auto json_length(const nlohmann::json &jsonValue) -> double;
    auto splitString(const std::string &str) -> std::vector<std::string>;
    auto splitJson(const nlohmann::json &jsonValue) -> nlohmann::json;
    auto upperJsonString(const nlohmann::json &data) -> nlohmann::json;
    auto lowerJsonString(const nlohmann::json &data) -> nlohmann::json;
    auto reduceJson(const nlohmann::json &jsonElem) -> nlohmann::json;
    auto mergeJson(const nlohmann::json &json1, const nlohmann::json &json2)
        -> nlohmann::json;
};
