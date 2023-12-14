#ifndef SEQ_AST_HPP
#define SEQ_AST_HPP

#include "RootAST.hpp"

class SeqAST : public RootAST
{
private:
    RootAST *first;
    RootAST *continuation;

public:
    SeqAST(RootAST *first, RootAST *continuation);
    void visit() override;
    Value *codegen(driver &drv) override;
};

#endif