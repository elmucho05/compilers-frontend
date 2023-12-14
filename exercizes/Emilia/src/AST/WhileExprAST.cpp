#include "WhileExprAST.hpp"

WhileExprAST::WhileExprAST(ExprAST *Cond, ExprAST *Body)
    : Cond(Cond), Body(Body)
{
    top = false;
}

void WhileExprAST::visit()
{
    std::cout << "while ";
    Cond->visit();
    std::cout << " do ";
    Body->visit();
    std::cout << " end ";
}

Value *WhileExprAST::codegen(driver &drv)
{
    if (gettop())
        return TopExpression(this, drv);

    const auto builder = drv.builder;

    Function *TheFunction = builder->GetInsertBlock()->getParent();

    BasicBlock *WhileHeaderBB = BasicBlock::Create(*drv.context, "while.header");
    BasicBlock *WhileBodyBB = BasicBlock::Create(*drv.context, "while.body");
    BasicBlock *ExitBB = BasicBlock::Create(*drv.context, "exit");

    builder->CreateBr(WhileHeaderBB);
    auto InitBB = builder->GetInsertBlock();

    // Header
    TheFunction->getBasicBlockList().insert(TheFunction->end(), WhileHeaderBB);
    builder->SetInsertPoint(WhileHeaderBB);

    Value *CondV = Cond->codegen(drv);
    if (!CondV)
        return nullptr;

    Value *ContinueCondition = builder->CreateFCmpONE(
        CondV,
        ConstantFP::get(*drv.context, APFloat(0.)),
        "whileCond");
    builder->CreateCondBr(ContinueCondition, WhileBodyBB, ExitBB);
    WhileHeaderBB = builder->GetInsertBlock();

    // Body
    TheFunction->getBasicBlockList().insert(TheFunction->end(), WhileBodyBB);
    builder->SetInsertPoint(WhileBodyBB);

    Value *BodyVal = Body->codegen(drv);
    if (!BodyVal)
        return nullptr;

    builder->CreateBr(WhileHeaderBB);
    WhileBodyBB = builder->GetInsertBlock();

    // EXIT
    TheFunction->getBasicBlockList().insert(TheFunction->end(), ExitBB);
    builder->SetInsertPoint(ExitBB);

    return BodyVal;
}