#ifndef ARRAY_ASSING_EXPR_AST_HPP
#define ARRAY_ASSING_EXPR_AST_HPP

#include "ExprAST.hpp"

class ArrayAssignExprAST : public ExprAST {
private:
	std::string VarName;
    ExprAST* Index;
    ExprAST* Val;
  
public:
	ArrayAssignExprAST(std::string VarName, ExprAST* Index, ExprAST* Val);
	void visit() override;
	Value *codegen(driver& drv) override;
};


#endif 