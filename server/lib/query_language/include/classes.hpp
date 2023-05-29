#pragma once

#include <variant>
#include "scaner.hpp"

class Binary;
class Grouping;
class Unary;
class LogicalExpr;
class FuncIn;
class Literal;

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
class ExprVisitor {
 public:
    virtual ~ExprVisitor()                = default;
    virtual void visit(Binary *Expr)       = 0;
    virtual void visit(Unary *Expr)        = 0;
    virtual void visit(Literal *Expr)      = 0;
    virtual void visit(LogicalExpr *Expr) = 0;
    virtual void visit(FuncIn *Expr)      = 0;
    virtual void visit(Grouping *Expr)     = 0;
};

// базовый класс аст дерева
class Expr {
 public:
    virtual ~Expr()                            = default;
    virtual void accept(ExprVisitor *visitor) = 0;
};

// класс для переменной, считанной из запроса
class Literal : public Expr {
 public:
    
    Literal(std::string v);
    Literal(double d);
    Literal(bool b);
    Literal(std::vector<std::string> json_namevec);
    Literal();

    value& get_value();
    std::vector<std::string> get_json_namevec();
    void accept(ExprVisitor *visitor) override;

 private:
    std::vector<std::string> json_namevec;
    value                    val;
};

// класс бинарных операций
class Binary : public Expr {
 public:

    Binary(std::unique_ptr<Expr> left_, token tok, std::unique_ptr<Expr> right_);

    Expr * get_leftptr();
    Expr * get_rightptr();
    token  get_opername();
    void accept(ExprVisitor *visitor) override;

 private:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    token                 oper;
};

class FuncIn : public Expr {
 public:

    FuncIn(std::unique_ptr<Expr> left_, std::unique_ptr<Expr> right_);

    Expr * get_leftptr();
    Expr * get_rightptr();
    void accept(ExprVisitor *visitor) override;

 private:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};


// элементарный класс унарных операций
class Unary : public Expr {
 public:

    Unary(std::unique_ptr<Expr> Expression_, token tok);

    Expr * get_expr();
    token  get_opername();
    void accept(ExprVisitor *visitor) override;
    
 private:
    std::unique_ptr<Expr> expression;
    token                 oper;
};


class LogicalExpr : public Expr {
 public:
    
    LogicalExpr(std::unique_ptr<Expr> left_,
                 token                 tok,
                 std::unique_ptr<Expr> right_);

    Expr * get_leftptr();
    Expr * get_rightptr();
    token  get_opername();
    void accept(ExprVisitor *visitor) override;

 private:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    token                 oper;
};


// класс для выражений в скобках
class Grouping : public Expr {
 public:
    Grouping(std::unique_ptr<Expr> Expression_);

    Expr * get_expr();
    void accept(ExprVisitor *visitor);

 private:
    std::unique_ptr<Expr> expression;
};




