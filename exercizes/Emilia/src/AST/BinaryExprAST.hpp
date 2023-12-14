#ifndef BINARY_EXPR_AST_HPP
#define BINARY_EXPR_AST_HPP

#include "ExprAST.hpp"

class BinaryExprAST : public ExprAST
{
private:
    char Op;
    ExprAST *LHS;
    ExprAST *RHS;

public:
    BinaryExprAST(char Op, ExprAST *LHS, ExprAST *RHS);
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif