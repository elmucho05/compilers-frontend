#ifndef UNARY_EXPR_AST_HPP
#define UNARY_EXPR_AST_HPP

#include "ExprAST.hpp"

class UnaryExprAST : public ExprAST
{
private:
    char Op;
    ExprAST *Expr;

public:
    UnaryExprAST(char Op, ExprAST *Expr);
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif