#pragma once
#include "parcer.h"

class interpreter : expr_visitor {
    public:
    interpreter();
    value interpret(expr* expression);
    
    private:
    value result;
    value evaluate(expr* expression);
    bool is_truthy(value val);
    bool is_equal(value left, value right);
    void visit(binary* expr);
    void visit(grouping* expr);
    void visit(unary* expr);
    void visit(literal* expr);
   // void visit(func_expr* expr);
    void visit(logical_expr* ex);
    
    void check_number_operand(token oper, value operand);
    void check_number_operands(token oper, value left, value right);
};