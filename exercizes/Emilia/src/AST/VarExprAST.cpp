#include "VarExprAST.hpp"
#include "Utils/LogError.hpp"

VarExprAST::VarExprAST(std::vector<std::pair<std::string, ExprAST *>> VarNames, ExprAST *Body)
	: VarNames(VarNames), Body(Body)
{
	top = false;
};

void VarExprAST::visit()
{
	std::cout << "var ";
	for (auto &Var : VarNames)
	{
		std::cout << Var.first << " = ";
		Var.second->visit();
	}
	std::cout << " do ";
	Body->visit();
	std::cout << " end ";
};

Value *VarExprAST::codegen(driver &drv)
{
	std::vector<AllocaInst *> OldBindings;

	Function *TheFunction = drv.builder->GetInsertBlock()->getParent();

	for (auto &Var : VarNames)
	{
		const std::string &VarName = Var.first;
		ExprAST *Init = Var.second;

		Value *InitVal = Init->codegen(drv);
		if (!InitVal)
			return nullptr;

		AllocaInst *Alloca;

		if (Init->getIsSize())
		{
			Value *blocks = drv.builder->CreateFPToUI(InitVal, Type::getInt32Ty(*drv.context), "blocks");
			Alloca = CreateEntryBlockAlloca(drv, TheFunction, VarName, blocks);
		}
		else
		{
			Alloca = CreateEntryBlockAlloca(drv, TheFunction, VarName);
			drv.builder->CreateStore(InitVal, Alloca);
		}

		OldBindings.push_back(drv.NamedValues[VarName]);

		drv.NamedValues[VarName] = Alloca;
	}

	Value *BodyVal = Body->codegen(drv);
	if (!BodyVal)
		return nullptr;

	for (unsigned i = 0, e = VarNames.size(); i != e; ++i)
		drv.NamedValues[VarNames[i].first] = OldBindings[i];

	return BodyVal;
};