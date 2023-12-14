#ifndef ROOT_AST_HPP
#define ROOT_AST_HPP

#include "llvm/IR/Value.h"
#include "../driver.hpp"

class RootAST
{
public:
    virtual ~RootAST(){};
    virtual void visit(){};
    virtual llvm::Value *codegen(driver &drv) { return nullptr; };
};

#endif