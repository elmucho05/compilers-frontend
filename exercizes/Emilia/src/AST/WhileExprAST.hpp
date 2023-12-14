#ifndef WHILE_EXPR_AST_HPP
#define WHILE_EXPR_AST_HPP

#include "ExprAST.hpp"

class WhileExprAST : public ExprAST
{
private:
    ExprAST *Cond;
    ExprAST *Body;

public:
    WhileExprAST(ExprAST *Cond, ExprAST *Body);
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif