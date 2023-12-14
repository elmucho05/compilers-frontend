#include "NumberExprAST.hpp"

NumberExprAST::NumberExprAST(double Val): Val(Val) { top = false; };
void NumberExprAST::visit() {
  std::cout << Val << " ";
};

Value *NumberExprAST::codegen(driver& drv) {  
  if (gettop()) return TopExpression(this, drv);
  else return ConstantFP::get(*drv.context, APFloat(Val));
};