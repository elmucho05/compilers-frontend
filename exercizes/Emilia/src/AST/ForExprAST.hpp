#ifndef FOR_EXPR_AST_HPP
#define FOR_EXPR_AST_HPP

#include "ExprAST.hpp"

class ForExprAST : public ExprAST {
private:
    std::string VarName;
    ExprAST* Start;
    ExprAST* End;
    ExprAST* Step;
    ExprAST* Body;
    
public:
    ForExprAST(
        const std::string &VarName, 
        ExprAST* Start,
        ExprAST* End, 
        ExprAST* Step,
        ExprAST* Body
    );
    void visit() override;
    Value *codegen(driver& drv) override;
};

#endif 