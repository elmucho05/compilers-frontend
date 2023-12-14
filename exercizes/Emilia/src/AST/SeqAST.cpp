#include "SeqAST.hpp"

SeqAST::SeqAST(RootAST *first, RootAST *continuation) : first(first), continuation(continuation){};

void SeqAST::visit()
{
    if (first != nullptr)
    {
        first->visit();
    }
    else
    {
        if (continuation == nullptr)
        {
            return;
        };
    };
    std::cout << ";";
    continuation->visit();
};

Value *SeqAST::codegen(driver &drv)
{
    if (first != nullptr)
    {
        Value *f = first->codegen(drv);
    }
    else
    {
        if (continuation == nullptr)
            return nullptr;
    }
    Value *c = continuation->codegen(drv);
    return nullptr;
};