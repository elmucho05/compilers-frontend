#include "UnaryExprAST.hpp"
#include "NumberExprAST.hpp"
#include "Utils/LogError.hpp"

UnaryExprAST::UnaryExprAST(char Op, ExprAST *Expr) : Op(Op), Expr(Expr) { top = false; };

void UnaryExprAST::visit()
{
	std::cout << "(" << Op << " ";
	if (Expr != nullptr)
		Expr->visit();
	std::cout << ")";
};

Value *UnaryExprAST::codegen(driver &drv)
{
	if (gettop())
		return TopExpression(this, drv);

	Value *val = Expr->codegen(drv);
	if (!val)
		return nullptr;

	switch (Op)
	{
	case '-':
	{
		NumberExprAST *minusOne = new NumberExprAST(-1.f);
		return drv.builder->CreateFMul(
			val,
			minusOne->codegen(drv),
			"inversionregister");
	}
	case '!':
	{
		Value *comp = drv.builder->CreateFCmpOEQ(
			val,
			ConstantFP::get(*drv.context, APFloat(0.0)), "boolnotregister");
		return drv.builder->CreateUIToFP(comp,Type::getDoubleTy(*drv.context),"notregister");
	}
	default:
		LogErrorV("Operatore unario non supportato");
		return nullptr;
	};
}