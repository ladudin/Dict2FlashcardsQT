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
    
    literal(std::string v);
    literal(double d);
    literal(bool b);
    literal(std::vector<std::string> json_namevec);
    literal();

    value& get_value();
    std::vector<std::string> get_json_namevec();
    void accept(expr_visitor *visitor) override;

 private:
    std::vector<std::string> json_namevec;
    value                    val;
};

// класс бинарных операций
class binary : public expr {
 public:

    binary(std::unique_ptr<expr> left_, token tok, std::unique_ptr<expr> right_);

    expr * get_leftptr();
    expr * get_rightptr();
    token  get_opername();
    void accept(expr_visitor *visitor) override;

 private:
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
    token                 oper;
};

class func_in : public expr {
 public:

    func_in(std::unique_ptr<expr> left_, std::unique_ptr<expr> right_);

    expr * get_leftptr();
    expr * get_rightptr();
    void accept(expr_visitor *visitor) override;

 private:
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
};


// элементарный класс унарных операций
class unary : public expr {
 public:

    unary(std::unique_ptr<expr> expression_, token tok);

    expr * get_expr();
    token  get_opername();
    void accept(expr_visitor *visitor) override;
    
 private:
    std::unique_ptr<expr> expression;
    token                 oper;
};


class logical_expr : public expr {
 public:
    
    logical_expr(std::unique_ptr<expr> left_,
                 token                 t,
                 std::unique_ptr<expr> right_);

    expr * get_leftptr();
    expr * get_rightptr();
    token  get_opername();
    void accept(expr_visitor *visitor) override;

 private:
    std::unique_ptr<expr> left;
    std::unique_ptr<expr> right;
    token                 oper;
};


// класс для выражений в скобках
class grouping : public expr {
 public:
    grouping(std::unique_ptr<expr> expression_);

    expr * get_expr();
    void accept(expr_visitor *visitor);

 private:
    std::unique_ptr<expr> expression;
};




