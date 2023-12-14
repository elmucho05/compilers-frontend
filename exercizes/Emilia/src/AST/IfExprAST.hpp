#ifndef IF_EXPR_AST_HPP
#define IF_EXPR_AST_HPP

#include "ExprAST.hpp"

class IfExprAST : public ExprAST {
private:
	ExprAST* Condition;
	ExprAST* Then;
	ExprAST* Else;
  
public:
	IfExprAST(ExprAST* Condition, ExprAST* Then, ExprAST* Else);
	void visit() override;
	Value *codegen(driver& drv) override;
};

#endif 