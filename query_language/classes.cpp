
#include "classes.h"


literal::literal(std::string v) : val(v) {};
literal::literal(double d) : val(d) {};
literal::literal(bool b) : val(b) {};
literal::literal(std::vector<std::string> json_namevec_) : json_namevec(json_namevec_) {};
literal::literal() : val() {};
literal::~literal() {}
void literal::accept(expr_visitor* visitor) {
    visitor->visit(this);
}

binary::binary(std::unique_ptr<expr> l, token tok, std::unique_ptr<expr> r) :
 left(std::move(l)), op(tok), right(std::move(r)) {};
binary::~binary() {}
void binary::accept(expr_visitor* visitor){
    visitor->visit(this);
}

unary::unary(std::unique_ptr<expr> expr_, token t) : ex(std::move(expr_)), op(t) {};
unary::~unary() {}

void unary::accept(expr_visitor* visitor){
    visitor->visit(this);
}

logical_expr::logical_expr(std::unique_ptr<expr> left_, token t, std::unique_ptr<expr> right_) :
left(std::move(left_)), oper(t), right(std::move(right_)) {};
logical_expr::~logical_expr() {}

void logical_expr::accept(expr_visitor* visitor) {
    visitor->visit(this);
}

func_in::func_in(std::unique_ptr<expr> left_, std::unique_ptr<expr> right_) :
 left(std::move(left_)), right(std::move(right_)) {};
func_in::~func_in() {}

void func_in::accept(expr_visitor* visitor) {
    visitor->visit(this);
}

grouping::grouping(std::unique_ptr<expr> expr_) : expression(std::move(expr_)) {};
grouping::~grouping() {};

void grouping::accept(expr_visitor* visitor){
    visitor->visit(this);
}