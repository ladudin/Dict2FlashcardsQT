#pragma once

#include "scaner.hpp"

class binary;
class grouping;
class unary;
class logical_expr;
class func_in;
class literal;

// элемент этой структуры является результатом действия
// функций аст дерева
struct value {
    token_type     val_type;
    bool           bool_val;
    double         doub_val;
    std::string    str_val;
    nlohmann::json json_val;

    value() : val_type(EMPTY) {
    }

    value(bool bool_val_) : val_type(BOOL), bool_val(bool_val_) {
    }

    value(nlohmann::json json_val_) : val_type(JSON), json_val(json_val_) {
    }

    value(double doub_val_) : val_type(DOUBLE), doub_val(doub_val_) {
    }

    value(std::string str_val_) : val_type(STRING), str_val(str_val_) {
    }
};

// интерпретатор аст дерева обязан определить
// все функции для посещения его вершин
class expr_visitor {
 public:
    virtual ~expr_visitor()                = default;
    virtual void visit(binary *expr)       = 0;
    virtual void visit(unary *expr)        = 0;
    virtual void visit(literal *expr)      = 0;
    virtual void visit(logical_expr *expr) = 0;
    virtual void visit(func_in *expr)      = 0;
    virtual void visit(grouping *expr)     = 0;
};

// базовый класс аст дерева
class expr {
 public:
    virtual ~expr()                            = default;
    virtual void accept(expr_visitor *visitor) = 0;
};

// класс для переменной, считанной из запроса
class literal : public expr {
 public:
    std::vector<std::string> json_namevec;
    value                    val;
    literal(std::string v);
    literal(double d);
    literal(bool b);
    literal(std::vector<std::string> json_namevec);
    literal();
    virtual ~literal(){};
    void accept(expr_visitor *visitor);
};

// класс бинарных операций
class binary : public expr {
 public:
    std::unique_ptr<expr> left;
    token                 op;
    std::unique_ptr<expr> right;

    binary(std::unique_ptr<expr> left_, token tok, std::unique_ptr<expr> right_);
    virtual ~binary(){};
    void accept(expr_visitor *visitor);
};

class func_in : public expr {
 public:
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;

    func_in(std::unique_ptr<expr> left_, std::unique_ptr<expr> right_);
    virtual ~func_in(){};
    void accept(expr_visitor *visitor);
};


// элементарный класс унарных операций
class unary : public expr {
 public:
    std::unique_ptr<expr> expression;
    token                 oper;

    unary(std::unique_ptr<expr> expression_, token tok);
    virtual ~unary(){};
    void accept(expr_visitor *visitor);
};


class logical_expr : public expr {
 public:
    std::unique_ptr<expr> left;
    token                 oper;
    std::unique_ptr<expr> right;

    logical_expr(std::unique_ptr<expr> left_,
                 token                 t,
                 std::unique_ptr<expr> right_);
    virtual ~logical_expr(){};
    void accept(expr_visitor *visitor);
};


// класс для выражений в скобках
class grouping : public expr {
 public:
    std::unique_ptr<expr> expression;

    grouping(std::unique_ptr<expr> expression_);
    virtual ~grouping(){};
    void accept(expr_visitor *visitor);
};




