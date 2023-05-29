#include "classes.hpp"


Literal::Literal(std::string v) : val(v){};
Literal::Literal(double d) : val(d){};
Literal::Literal(bool b) : val(b){};
Literal::Literal(std::vector<std::string> json_namevec_)
    : json_namevec(json_namevec_){};
Literal::Literal() : val(){};


value& Literal::get_value()
{
    return val;
}

std::vector<std::string> Literal::get_json_namevec()
{
    return json_namevec;
}

void Literal::accept(ExprVisitor *visitor)
{
    visitor->visit(this);
}



Binary::Binary(std::unique_ptr<Expr> left_, token tok, std::unique_ptr<Expr> right_)
    : left(std::move(left_)), oper(tok), right(std::move(right_)){};

void Binary::accept(ExprVisitor *visitor)
{
    visitor->visit(this);
}

Expr * Binary::get_leftptr()
{
    return left.get();
}

Expr * Binary::get_rightptr()
{
    return right.get();
}

token  Binary::get_opername()
{
    return oper;
}


Unary::Unary(std::unique_ptr<Expr> expr_, token tok)
    : expression(std::move(expr_)), oper(tok){};

Expr * Unary::get_expr()
{
    return expression.get();
}

token  Unary::get_opername()
{
    return oper;
}

void Unary::accept(ExprVisitor *visitor) {
    visitor->visit(this);
}


LogicalExpr::LogicalExpr(std::unique_ptr<Expr> left_,
                           token                 tok,
                           std::unique_ptr<Expr> right_)
    : left(std::move(left_)), oper(tok), right(std::move(right_)){};

void LogicalExpr::accept(ExprVisitor *visitor) {
    visitor->visit(this);
}

Expr * LogicalExpr::get_leftptr()
{
    return left.get();
}

Expr * LogicalExpr::get_rightptr()
{
    return right.get();
}

token  LogicalExpr::get_opername()
{
    return oper;
}


FuncIn::FuncIn(std::unique_ptr<Expr> left_, std::unique_ptr<Expr> right_)
    : left(std::move(left_)), right(std::move(right_)){};

void FuncIn::accept(ExprVisitor *visitor)
{
    visitor->visit(this);
}

Expr * FuncIn::get_leftptr()
{
    return left.get();
}

Expr * FuncIn::get_rightptr()
{
    return right.get();
}


Grouping::Grouping(std::unique_ptr<Expr> Expr_)
    : expression(std::move(Expr_)){};

void Grouping::accept(ExprVisitor *visitor)
{
    visitor->visit(this);
}

Expr * Grouping::get_expr()
{
    return expression.get();
}