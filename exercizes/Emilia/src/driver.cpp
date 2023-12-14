#include "driver.hpp"
#include "AST/RootAST.hpp"
#include "AST/ExprAST.hpp"
#include "AST/FunctionAST.hpp"
#include "AST/Utils/LogError.hpp"

driver::driver() : trace_parsing(false), trace_scanning(false), ast_print(false)
{
	context = new LLVMContext;
	module = new Module("Kaleidoscope", *context);
	builder = new IRBuilder(*context);
};

int driver::parse(const std::string &f)
{
	file = f;
	location.initialize(&file);
	scan_begin();
	yy::parser parser(*this);
	parser.set_debug_level(trace_parsing);
	int res = parser.parse();
	scan_end();
	return res;
}

void driver::codegen()
{
	if (ast_print)
		root->visit();
	std::cout << std::endl;
	root->codegen(*this);
};

Value *TopExpression(ExprAST *E, driver &drv)
{
	E->toggle();
	PrototypeAST *Proto = new PrototypeAST("__espr_anonima" + std::to_string(++drv.Cnt), std::vector<std::string>());
	Proto->noemit();
	FunctionAST *F = new FunctionAST(std::move(Proto), E);
	auto *FnIR = F->codegen(drv);
	FnIR->eraseFromParent();
	return nullptr;
};

AllocaInst *CreateEntryBlockAlloca(
	driver &drv,
	Function *TheFunction,
	const std::string &VarName,
	const Value *ArraySize)
{
	IRBuilder<> TmpB(
		&TheFunction->getEntryBlock(),
		TheFunction->getEntryBlock().begin());

	Value *ActualSize = (Value *)ArraySize;
	if (!ArraySize)
		return TmpB.CreateAlloca(Type::getDoubleTy(*drv.context), 0, VarName.c_str());

	return TmpB.CreateAlloca(Type::getDoubleTy(*drv.context), ActualSize, VarName.c_str());
}