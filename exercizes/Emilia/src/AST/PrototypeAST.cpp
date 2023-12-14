#include "PrototypeAST.hpp"

PrototypeAST::PrototypeAST(std::string Name, std::vector<std::string> Args) : Name(Name), Args(std::move(Args)) { emit = true; };
const std::string &PrototypeAST::getName() const { return Name; };
const std::vector<std::string> &PrototypeAST::getArgs() const { return Args; };
void PrototypeAST::visit()
{
    std::cout << "extern " << getName() << "( ";
    for (auto it = getArgs().begin(); it != getArgs().end(); ++it)
    {
        std::cout << *it << ' ';
    };
    std::cout << ')';
};

void PrototypeAST::noemit() { emit = false; };

bool PrototypeAST::emitp() { return emit; };

Function *PrototypeAST::codegen(driver &drv)
{
    std::vector<Type *> Doubles(Args.size(), Type::getDoubleTy(*drv.context));
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(*drv.context), Doubles, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, Name, *drv.module);

    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(Args[Idx++]);

    if (emitp())
    {
        F->print(errs());
        fprintf(stderr, "\n");
    };

    return F;
}
