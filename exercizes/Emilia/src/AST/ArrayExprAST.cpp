#include "ArrayExprAST.hpp"
#include "Utils/LogError.hpp"

ArrayExprAST::ArrayExprAST(std::string VarName,ExprAST *Index) : VarName(VarName), Index(Index){
    top = false;
};

void ArrayExprAST::visit()
{
    std::cout << VarName;
    std::cout << " [ ";
    Index->visit();
    std::cout << " ] ";
};

Value *ArrayExprAST::codegen(driver &drv)
{
    if (gettop())
        return TopExpression(this, drv);

    auto array = drv.NamedValues[VarName];
    if(!array)
    {
        LogErrorV(VarName + " Variabile non definita");
        return nullptr;
    }
    
    if(!array->isArrayAllocation())
    {
        LogErrorV(VarName +" Variabile non indicizzabile");
        return nullptr;
    }

    auto idx = Index->codegen(drv);
    if(!idx)
        return nullptr;

    Value* indexInteger = drv.builder->CreateFPToUI(idx, Type::getInt32Ty(*drv.context), "indexInteger");
    
    Value* offsetPosition = drv.builder->CreateInBoundsGEP(Type::getDoubleTy(*drv.context),array,indexInteger,"arrayAccess");
    return drv.builder->CreateLoad(Type::getDoubleTy(*drv.context), offsetPosition, "accessedValue");
}