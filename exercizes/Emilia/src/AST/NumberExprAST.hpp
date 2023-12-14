#ifndef NUMBER_EXPR_AST_HPP
#define NUMBER_EXPR_AST_HPP

#include "ExprAST.hpp"

class NumberExprAST : public ExprAST {
private:
  double Val;

public:
  NumberExprAST(double Val);
  void visit() override;
  Value *codegen(driver& drv) override;
};

#endif