#include "ForExprAST.hpp"

ForExprAST::ForExprAST(const std::string &VarName, ExprAST *Start, ExprAST *End, ExprAST *Step, ExprAST *Body): VarName(VarName), Start(Start), End(End), Step(Step), Body(Body)
{
    top = false;
}

void ForExprAST::visit()
{
    std::cout << "for " << VarName;
    std::cout << " = ";
    Start->visit();
    std::cout << " , ";
    End->visit();
    std::cout << " , ";
    Step->visit();
    std::cout << " do ";
    Body->visit();
}

Value *ForExprAST::codegen(driver &drv)
{
    if (gettop())
        return TopExpression(this, drv);

    const auto builder = drv.builder;

    Function *TheFunction = builder->GetInsertBlock()->getParent();

    AllocaInst *Alloca = CreateEntryBlockAlloca(drv, TheFunction, VarName);

    BasicBlock *ForHeaderBB = BasicBlock::Create(*drv.context, "for.header");
    BasicBlock *ForBodyBB = BasicBlock::Create(*drv.context, "for.body");
    BasicBlock *ForLatchBB = BasicBlock::Create(*drv.context, "for.latch");
    BasicBlock *ExitBB = BasicBlock::Create(*drv.context, "exit");

    Value *StartVal = Start->codegen(drv);
    if (!StartVal)
        return nullptr;

    builder->CreateStore(StartVal, Alloca);

    builder->CreateBr(ForHeaderBB);
    auto InitBB = builder->GetInsertBlock();

    // Header
    TheFunction->getBasicBlockList().insert(TheFunction->end(), ForHeaderBB);
    builder->SetInsertPoint(ForHeaderBB);

    AllocaInst *OldVal = drv.NamedValues[VarName];
    drv.NamedValues[VarName] = Alloca;

    Value *CondV = End->codegen(drv);
    if (!CondV)
        return nullptr;

    Value *ContinueCondition = builder->CreateFCmpONE(
        CondV,
        ConstantFP::get(*drv.context, APFloat(0.)),
        "forCond");
    builder->CreateCondBr(ContinueCondition, ForBodyBB, ExitBB);
    ForHeaderBB = builder->GetInsertBlock();

    // Body
    TheFunction->getBasicBlockList().insert(TheFunction->end(), ForBodyBB);
    builder->SetInsertPoint(ForBodyBB);

    Value *BodyVal = Body->codegen(drv);
    if (!BodyVal)
        return nullptr;

    builder->CreateBr(ForLatchBB);
    ForBodyBB = builder->GetInsertBlock();

    // Latch
    TheFunction->getBasicBlockList().insert(TheFunction->end(), ForLatchBB);
    builder->SetInsertPoint(ForLatchBB);

    Value *StepVal = Step->codegen(drv);
    if (!StepVal)
        return nullptr;

    Type *DoubleTy = Type::getDoubleTy(*drv.context);
    Value *CurVar = builder->CreateLoad(DoubleTy, Alloca);
    Value *NextVal = builder->CreateFAdd(CurVar, StepVal, "nextVal");
    builder->CreateStore(NextVal, Alloca);

    builder->CreateBr(ForHeaderBB);
    ForLatchBB = builder->GetInsertBlock();

    // EXIT
    TheFunction->getBasicBlockList().insert(TheFunction->end(), ExitBB);
    builder->SetInsertPoint(ExitBB);

    if (OldVal)
        drv.NamedValues[VarName] = OldVal;
    else
        drv.NamedValues.erase(VarName);

    return BodyVal;
}