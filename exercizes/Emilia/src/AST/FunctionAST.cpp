#include "FunctionAST.hpp"
#include "ExprAST.hpp"
#include "Utils/LogError.hpp"

FunctionAST::FunctionAST(PrototypeAST *Proto, ExprAST *Body) : Proto(Proto), Body(Body)
{
    if (Body == nullptr)
        external = true;
    else
        external = false;
};

void FunctionAST::visit()
{
    std::cout << Proto->getName() << "( ";
    for (auto it = Proto->getArgs().begin(); it != Proto->getArgs().end(); ++it)
    {
        std::cout << *it << ' ';
    };
    std::cout << ')';
    Body->visit();
};

Function *FunctionAST::codegen(driver &drv)
{
    // Verifica che non esiste già, nel contesto, una funzione con lo stesso nome
    std::string name = Proto->getName();
    Function *TheFunction = drv.module->getFunction(name);
    // E se non esiste prova a definirla
    if (TheFunction)
    {
        LogErrorV("Funzione " + name + " già definita");
        return nullptr;
    }
    if (!TheFunction)
        TheFunction = Proto->codegen(drv);
    if (!TheFunction)
        return nullptr; // Se la definizione "fallisce" restituisce nullptr

    // Crea un blocco di base in cui iniziare a inserire il codice
    BasicBlock *BB = BasicBlock::Create(*drv.context, "entry", TheFunction);
    drv.builder->SetInsertPoint(BB);

    // Registra gli argomenti nella symbol table
    drv.NamedValues.clear();
    for (auto &Arg : TheFunction->args())
    {
        AllocaInst *Alloca = CreateEntryBlockAlloca(drv, TheFunction, std::string(Arg.getName()));
        drv.builder->CreateStore(&Arg, Alloca);
        drv.NamedValues[std::string(Arg.getName())] = Alloca;
    }

    if (Value *RetVal = Body->codegen(drv))
    {
        // Termina la creazione del codice corrispondente alla funzione
        drv.builder->CreateRet(RetVal);

        // Effettua la validazione del codice e un controllo di consistenza
        verifyFunction(*TheFunction);

        TheFunction->print(errs());
        fprintf(stderr, "\n");
        return TheFunction;
    }

    // Errore nella definizione. La funzione viene rimossa
    TheFunction->eraseFromParent();
    return nullptr;
};