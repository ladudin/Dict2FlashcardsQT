#include "classes.hpp"


literal::literal(std::string v) : val(v){};
literal::literal(double d) : val(d){};
literal::literal(bool b) : val(b){};
literal::literal(std::vector<std::string> json_namevec_)
    : json_namevec(json_namevec_){};
literal::literal() : val(){};


value& literal::get_value()
{
    return val;
}

std::vector<std::string> literal::get_json_namevec()
{
    return json_namevec;
}

void literal::accept(expr_visitor *visitor)
{
    visitor->visit(this);
}



binary::binary(std::unique_ptr<expr> left_, token tok, std::unique_ptr<expr> right_)
    : left(std::move(left_)), oper(tok), right(std::move(right_)){};

void binary::accept(expr_visitor *visitor)
{
    visitor->visit(this);
}

expr * binary::get_leftptr()
{
    return left.get();
}

expr * binary::get_rightptr()
{
    return right.get();
}

token  binary::get_opername()
{
    return oper;
}


unary::unary(std::unique_ptr<expr> expr_, token tok)
    : expression(std::move(expr_)), oper(tok){};

expr * unary::get_expr()
{
    return expression.get();
}

token  unary::get_opername()
{
    return oper;
}

void unary::accept(expr_visitor *visitor) {
    visitor->visit(this);
}


logical_expr::logical_expr(std::unique_ptr<expr> left_,
                           token                 tok,
                           std::unique_ptr<expr> right_)
    : left(std::move(left_)), oper(tok), right(std::move(right_)){};

void logical_expr::accept(expr_visitor *visitor) {
    visitor->visit(this);
}

expr * logical_expr::get_leftptr()
{
    return left.get();
}

expr * logical_expr::get_rightptr()
{
    return right.get();
}

token  logical_expr::get_opername()
{
    return oper;
}


func_in::func_in(std::unique_ptr<expr> left_, std::unique_ptr<expr> right_)
    : left(std::move(left_)), right(std::move(right_)){};

void func_in::accept(expr_visitor *visitor)
{
    visitor->visit(this);
}

expr * func_in::get_leftptr()
{
    return left.get();
}

expr * func_in::get_rightptr()
{
    return right.get();
}


grouping::grouping(std::unique_ptr<expr> expr_)
    : expression(std::move(expr_)){};

void grouping::accept(expr_visitor *visitor)
{
    visitor->visit(this);
}

expr * grouping::get_expr()
{
    return expression.get();
}