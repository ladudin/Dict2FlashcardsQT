#pragma once
#include "parser.hpp"

class interpreter : ExprVisitor {
 public:
    interpreter();
    value interpret(Expr * expression, nlohmann::json card_);

 private:
    nlohmann::json card;
    value          result;
    auto           evaluate(Expr *expression) -> value;
    auto           is_truthy(value val) -> bool;
    auto           is_equal(value left, value right) -> bool;
    void           visit(Binary *expr) override;
    void           visit(Grouping *expr) override;
    void           visit(Unary *expr) override;
    void           visit(Literal *expr) override;
    void           visit(FuncIn *expr) override;
    void           visit(LogicalExpr *ex) override;
    auto find_word_inJson(std::string word, nlohmann::json jsonValue) -> bool;
    void check_json_operand(value operand);
    void check_number_operand(value operand);
    void check_number_operands(token oper, value left, value right);
    auto find_json_value(const nlohmann::json &card, std::vector<std::string>)
        -> nlohmann::json;
    auto json_length(const nlohmann::json &jsonValue) -> double;
    auto split_string(const std::string &str) -> std::vector<std::string>;
    auto split_json(const nlohmann::json &jsonValue) -> nlohmann::json;
    auto upper_json_string(const nlohmann::json &data) -> nlohmann::json;
    auto lower_json_string(const nlohmann::json &data) -> nlohmann::json;
    auto reduce_json(const nlohmann::json &jsonElem) -> nlohmann::json;
    auto get_self_keys(const nlohmann::json& json_value) -> nlohmann::json;
    auto handle_any_key(const nlohmann::json& json_value,
                    const std::vector<std::string>& levels_vec,
                    size_t current_index) -> nlohmann::json;
    auto mergeJson(const nlohmann::json &jsonLeft, const nlohmann::json &jsonRight)
        -> nlohmann::json;
};
