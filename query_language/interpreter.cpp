#include "interpreter.h"

interpreter::interpreter() {};

value interpreter::interpret(expr* expression) {
    
    value result = evaluate(expression);
    return result;
}


value interpreter::evaluate(expr* expression){
    expression->accept(this);
    return result;
}



bool interpreter::is_truthy(value val){
    if (val.val_type == EMPTY) return false;
    if (val.val_type == DOUBLE) return val.doub_val != 0;
    if (val.val_type == BOOL) return val.bool_val;
    return true;
}

bool interpreter::is_equal(value left, value right){
    if (left.val_type == BOOL && right.val_type == BOOL) return left.bool_val == right.bool_val;
    if (left.val_type == DOUBLE && right.val_type == DOUBLE) return left.doub_val == right.doub_val;
    if (left.val_type == JSON && right.val_type == JSON) return left.json_val == right.json_val;
    if (left.val_type == EMPTY && right.val_type == EMPTY) return true;
    return false;
}


/*void interpreter::check_number_operand(token oper, value operand){
    if (operand.val_type == DOUBLE) 
        return;
    // обработать ошибку 
}*/

/*void interpreter::check_number_operands(token oper, value left, value right){
    if (left.val_type == DOUBLE && right.val_type == DOUBLE){ 
        if (right.doub_val == 0 && oper.type == SLASH)
        //   обработать ошибку 
        return;
        }
    // обработать ошибку 
}*/

void interpreter::visit(binary* expr){
    value left = evaluate(expr->left);
    value right = evaluate(expr->right);
    switch(expr->op.type){
        case PLUS:
            if (left.val_type == DOUBLE && right.val_type == DOUBLE)
                result = value(left.doub_val + right.doub_val);
            else
                // обработать ошибку
            break;
        case MINUS:
            //проверить типы 
            result = value(left.doub_val - right.doub_val);
            break;    
        case STAR:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val * right.doub_val);
            break;
        case SLASH:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val / right.doub_val);
            break;    
        case LESS:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val < right.doub_val);
            break;   
        case LESS_EQUAL:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val <= right.doub_val);
            break; 
        case GREATER:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val > right.doub_val);
            break;
        case GREATER_EQUAL:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val >= right.doub_val);
            break;
        case BANG_EQUAL:
            result = value(!is_equal(left,right));
            break;
        case EQUAL_EQUAL:
            result = value(is_equal(left,right));
            break;
        default:
            result = value();
            break;
    }
}

void interpreter::visit(grouping* expr){
    expr->accept(this);
}	

void interpreter::visit(unary* expr){
    value right = evaluate(expr->ex);

    switch(expr->op.type){
        case MINUS: 
            //check_number_operand(expr->op, right);
            result = value(-right.doub_val);
            break;
        case BANG:
            if (is_truthy(right))
                result = value(!is_truthy(right));
            break;
        default:
            result = value();
            break;
    }
}

void interpreter::visit(literal* expr){
    result = expr->val; 
}

/*void interpreter::visit(expr_visitor* expr){
    value callee = evaluate(expr->callee);

    std::vector<value> arguments;
    for (auto& a : expr->arguments){
        arguments.emplace_back(evaluate(a));
    }
    if (callee.v_type != CALLABLE_VALUE)
        throw lox_runtime_error(expr->paren, "Can only call functions and classes.");

    lox_callable* function = callee.callable_value;
    
    if (arguments.size() > function->arity()){
        throw lox_runtime_error(expr->paren, std::string("Expected " + std::to_string(function->arity()) +
            " arguments, got " + std::to_string(arguments.size()) + " ."));
    }
    result = function->call(this, arguments);
}*/


void interpreter::visit(logical_expr* ex){
    value left = evaluate(ex->left);
    if (ex->oper.type == OR){
        if (is_truthy(left)){
            result = left;
            return;
        } 
    }
    else{
        if (!is_truthy(left)){
            result = left;
            return;
        }
    }
    result = evaluate(ex->right);
}
