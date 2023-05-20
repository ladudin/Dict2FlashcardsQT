#pragma once
#include "parcer.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class interpreter : expr_visitor {
 public:
    interpreter();
    value interpret(expr *expression, nlohmann::json card_);

 private:
    nlohmann::json card;
    value          result;
    value          evaluate(expr *expression);
    bool           is_truthy(value val);
    bool           is_equal(value left, value right);
    void           visit(binary *expr);
    void           visit(grouping *expr);
    void           visit(unary *expr);
    void           visit(literal *expr);
    void           visit(func_in *expr);
    void           visit(logical_expr *ex);
    bool           find_word_inJson(std::string word, nlohmann::json jsonValue);
    void           check_number_operand(token oper, value operand);
    void           check_number_operands(token oper, value left, value right);
    nlohmann::json find_json_value(const nlohmann::json &card,
                                   std::vector<std::string>);
};
