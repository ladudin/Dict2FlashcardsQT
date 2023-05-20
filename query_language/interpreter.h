#pragma once
#include "parcer.h"

class interpreter : expr_visitor {
    public:
    interpreter();
    value interpret(std::unique_ptr<expr> expression, json card_);
    
    private:
    json card;
    value result;
    value evaluate(const std::unique_ptr<expr>& expression);
    bool is_truthy(value val);
    bool is_equal(value left, value right);
    void visit( binary* expr);
    void visit( grouping* expr);
    void visit( unary* expr);
    void visit( literal* expr);
    void visit( func_in* expr);
    void visit( logical_expr* ex);
    bool find_word_inJson(std::string word, json jsonValue);
    void check_number_operand(token oper, value operand);
    void check_number_operands(token oper, value left, value right);
    json find_json_value(const json& card, std::vector<std::string>);
};