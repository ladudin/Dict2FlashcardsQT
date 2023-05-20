
#include "classes.h"

literal::literal(std::string v) : val(v){};
literal::literal(double d) : val(d){};
literal::literal(bool b) : val(b){};
literal::literal(std::vector<std::string> json_namevec_)
    : json_namevec(json_namevec_){};
literal::literal() : val(){};

literal::~literal() {
}

void literal::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

binary::binary(expr *l, token tok, expr *r) : left(l), op(tok), right(r){};

binary::~binary() {
    delete left;
    delete right;
}

void binary::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

unary::unary(expr *e, token t) : ex(e), op(t){};

unary::~unary() {
    delete ex;
}

void unary::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

logical_expr::logical_expr(expr *l, token t, expr *r)
    : left(l), oper(t), right(r){};

logical_expr::~logical_expr() {
    delete left;
    delete right;
}

void logical_expr::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

func_in::func_in(expr *l, expr *r) : left(l), right(r){};

func_in::~func_in() {
    delete left;
    delete right;
}

void func_in::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

grouping::grouping(expr *e) : expression(e){};

grouping::~grouping() {
    delete expression;
}

void grouping::accept(expr_visitor *visitor) {
    visitor->visit(this);
}
