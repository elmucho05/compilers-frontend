#ifndef FUNCTION_AST_HPP
#define FUNCTION_AST_HPP

#include "PrototypeAST.hpp"

class FunctionAST : public RootAST
{
private:
    PrototypeAST *Proto;
    ExprAST *Body;
    bool external;

public:
    FunctionAST(PrototypeAST *Proto, ExprAST *Body);
    void visit() override;
    Function *codegen(driver &drv) override;
};

#endif // !FUNCTION_AST_HPP