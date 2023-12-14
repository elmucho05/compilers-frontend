#ifndef CALL_EXPR_AST_HPP
#define CALL_EXPR_AST_HPP

#include "ExprAST.hpp"
#include <string>
#include <vector>

class CallExprAST : public ExprAST
{
private:
    std::string Callee;
    std::vector<ExprAST *> Args;

public:
    CallExprAST(std::string Callee, std::vector<ExprAST *> Args);
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif