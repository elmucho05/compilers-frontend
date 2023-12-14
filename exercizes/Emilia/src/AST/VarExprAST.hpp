#ifndef VAR_EXPR_AST_HPP
#define VAR_EXPR_AST_HPP

#include "ExprAST.hpp"
#include <string>

class VarExprAST : public ExprAST
{
private:
    std::vector<std::pair<std::string, ExprAST *>> VarNames;
    ExprAST *Body;

public:
    VarExprAST(std::vector<std::pair<std::string, ExprAST *>> VarNames, ExprAST *Body);
    const std::string &getName() const;
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif