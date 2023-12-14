#include "CallExprAST.hpp"
#include "Utils/LogError.hpp"

/********************* Call Expression Tree ***********************/
CallExprAST::CallExprAST(std::string Callee, std::vector<ExprAST *> Args) : Callee(Callee), Args(std::move(Args))
{
    top = false;
};

void CallExprAST::visit()
{
    std::cout << Callee << "( ";
    for (ExprAST *arg : Args)
    {
        arg->visit();
    };
    std::cout << ')';
};

Value *CallExprAST::codegen(driver &drv)
{
    if (gettop())
    {
        return TopExpression(this, drv);
    }
    else
    {
        // Cerchiamo la funzione nell'ambiente globale
        Function *CalleeF = drv.module->getFunction(Callee);
        if (!CalleeF)
        {
            LogErrorV("Funzione non definita");
            return nullptr;
        }
        // Controlliamo che gli argomenti coincidano in numero coi parametri
        if (CalleeF->arg_size() != Args.size())
        {
            LogErrorV("Numero di argomenti non corretto");
            return nullptr;
        }
        std::vector<Value *> ArgsV;
        for (auto arg : Args)
        {
            ArgsV.push_back(arg->codegen(drv));
            if (!ArgsV.back())
                return nullptr;
        }
        return drv.builder->CreateCall(CalleeF, ArgsV, "calltmp");
    }
}