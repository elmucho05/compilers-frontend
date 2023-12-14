#ifndef VARIABLE_EXPR_AST_HPP
#define VARIABLE_EXPR_AST_HPP

#include "ExprAST.hpp"
#include <string>

class VariableExprAST : public ExprAST
{
private:
    std::string Name;

public:
    VariableExprAST(std::string &Name);
    const std::string &getName() const;
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif