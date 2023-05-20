#pragma once
#include "scaner.h"

class binary;
class grouping;
class unary;
class logical_expr;
class func_in;
class literal;

// enum value_type{BOOL, JSON, DOUBLE, EMPTY};

struct value {
    token_type  val_type;
    bool        bool_val;
    double      doub_val;
    std::string str_val;
    json        json_val;

    value() : val_type(EMPTY) {
    }

    value(bool bool_val_) : val_type(BOOL), bool_val(bool_val_) {
    }

    value(json json_val_) : val_type(JSON), json_val(json_val_) {
    }

    value(double doub_val_) : val_type(DOUBLE), doub_val(doub_val_) {
    }

    value(std::string str_val_) : val_type(STRING), str_val(str_val_) {
    }
};

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

class expr {
 public:
    virtual ~expr()                            = default;
    virtual void accept(expr_visitor *visitor) = 0;
};

class literal : public expr {
 public:
    std::vector<std::string> json_namevec;
    value                    val;
    literal(std::string v);
    literal(double d);
    literal(bool b);
    literal(std::vector<std::string> json_namevec);
    literal();
    virtual ~literal();
    void accept(expr_visitor *visitor);
};

class binary : public expr {
 public:
    expr *left;
    token op;
    expr *right;

    binary(expr *l, token tok, expr *r);
    virtual ~binary();
    void accept(expr_visitor *visitor);
};

class func_in : public expr {
 public:
    expr *left;
    expr *right;

    func_in(expr *l, expr *r);
    virtual ~func_in();
    void accept(expr_visitor *visitor);
};

class unary : public expr {
 public:
    expr *ex;
    token op;

    unary(expr *e, token t);
    virtual ~unary();
    void accept(expr_visitor *visitor);
};

class logical_expr : public expr {
 public:
    expr *left;
    token oper;
    expr *right;

    logical_expr(expr *l, token t, expr *r);
    virtual ~logical_expr();
    void accept(expr_visitor *visitor);
};

class grouping : public expr {
 public:
    expr *expression;

    grouping(expr *e);
    virtual ~grouping();
    void accept(expr_visitor *visitor);
};
