#include "ArrayAssignExprAST.hpp"
#include "Utils/LogError.hpp"

ArrayAssignExprAST::ArrayAssignExprAST(std::string VarName, ExprAST *Index, ExprAST *Val) : VarName(VarName), Index(Index), Val(Val)
{
    top = false;
};

void ArrayAssignExprAST::visit()
{
    std::cout << VarName;
    std::cout << " [ ";
    Index->visit();
    std::cout << " ] ";
    std::cout << " = ";
    Val->visit();
};

Value *ArrayAssignExprAST::codegen(driver &drv)
{
    if (gettop())
        return TopExpression(this, drv);

    auto array = drv.NamedValues[VarName];
    if (!array)
    {
        LogErrorV(VarName + " Variabile non definita");
        return nullptr;
    }

    if (!array->isArrayAllocation())
    {
        LogErrorV(VarName + " Variabile non indicizzabile");
        return nullptr;
    }

    auto idx = Index->codegen(drv);
    if (!idx)
        return nullptr;

    Value *indexInteger = drv.builder->CreateFPToUI(idx, Type::getInt32Ty(*drv.context), "indexInteger");

    Value *offsetPosition = drv.builder->CreateInBoundsGEP(Type::getDoubleTy(*drv.context), array, indexInteger, "arrayAccess");

    auto value = Val->codegen(drv);
    if (!value)
        return nullptr;

    return drv.builder->CreateStore(value, offsetPosition);
}