#ifndef DRIVER_HPP
#define DRIVER_HPP
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <variant>

#include "parser.hpp"

using namespace llvm;

# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
YY_DECL;

class driver{
public:
    driver();
    std::map<std::string, AllocaInst*> NamedValues;
    RootAST* root;
    int parse (const std::string& f);
    std::string file;
    bool trace_parsing;
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;
    yy::location location;
    void codegen();
};

typedef std::variant<std::string,double> lexval;
const lexval NONE = 0.0;

class RootAST {
public:
    virtual ~RootAST() {};
    virtual lexval getLexVal() const {return NONE;};
    virtual Value *codegen(driver& drv) { return nullptr; };
};

class SeqAST : public RootAST {
private:
    RootAST* first;
    RootAST* continuation;

public:
    SeqAST(RootAST* first, RootAST* continuation);
    Value *codegen(driver& drv) override;
};

class StmtAST : public RootAST {
private:
    RootAST* stmt;

public:
    StmtAST(RootAST* stmt);
    Value *codegen(driver& drv) override;
};

class GlobalVarAST : public RootAST {
protected:
    std::string Name;

public:
    GlobalVarAST(const std::string& Name);
    lexval getLexVal() const override;
    virtual Value *codegen(driver &drv) override;
};

class GlobalArrayAST : public GlobalVarAST {
private:
    double itemNum;

public:
    GlobalArrayAST(const std::string& Name, double itemNum);
    Value *codegen(driver &drv) override;
};

class ExprAST : public RootAST {};

class NumberExprAST : public ExprAST {
private:
    double Val;

public:
    NumberExprAST(double Val);
    lexval getLexVal() const override;
    Value *codegen(driver& drv) override;
};

class VariableExprAST : public ExprAST {
private:
    std::string Name;
  
public:
    VariableExprAST(const std::string &Name);
    lexval getLexVal() const override;
    Value *codegen(driver& drv) override;
};

class ArrayExprAST : public ExprAST {
private:
    std::string Name;
    ExprAST* Idx;
  
public:
    ArrayExprAST(const std::string &Name, ExprAST* Idx);
    lexval getLexVal() const override;
    Value *codegen(driver& drv) override;
};

class BinaryExprAST : public ExprAST {
private:
    char Op;
    ExprAST* LHS;
    ExprAST* RHS;

public:
    BinaryExprAST(char Op, ExprAST* LHS, ExprAST* RHS);
    Value *codegen(driver& drv) override;
};

class UnaryExprAST : public ExprAST {
private:
    char Op;
    ExprAST* Val;

public:
    UnaryExprAST(char Op, ExprAST* Val);
    Value *codegen(driver& drv) override;
};

class CallExprAST : public ExprAST {
private:
    std::string Callee;
    std::vector<ExprAST*> Args;

public:
    CallExprAST(std::string Callee, std::vector<ExprAST*> Args);
    lexval getLexVal() const override;
    Value *codegen(driver& drv) override;
};

class IfExprAST : public ExprAST {
private:
    ExprAST* Cond;
    ExprAST* TrueExp;
    ExprAST* FalseExp;
public:
    IfExprAST(ExprAST* Cond, ExprAST* TrueExp, ExprAST* FalseExp);
    Value *codegen(driver& drv) override;
};

class IfStmtAST : public RootAST {
private:
    ExprAST* Cond;
    StmtAST* TrueStmt;
    StmtAST* FalseStmt;
public:
    IfStmtAST(ExprAST* Cond, StmtAST* TrueStmt, StmtAST* FalseStmt);
    Value *codegen(driver& drv) override;
};

class ForStmtAST : public RootAST{
private:
    InitAST* Init;
    ExprAST* Cond;
    RootAST* Assignment;
    StmtAST* Stmt;
public:
    ForStmtAST(InitAST* Init, ExprAST* Cond, RootAST* Assignment, StmtAST* Stmt);
    Value *codegen(driver& drv) override;
};

class BlockAST : public ExprAST {
private:
    std::vector<BindingAST*> Def;
    std::vector<StmtAST*> Stmts;
public:
    BlockAST(std::vector<BindingAST*> Def, std::vector<StmtAST*> Stmts);
    Value *codegen(driver& drv) override;
}; 
/*
Classe che ci aiuta a gestire l'inizializzazione del for. Precisamente ci permette di distingure la fase di init oppure l'assegnameto:
for (int i=0)
for (i=0)
- Se siamo in fase di inizializzazione, abbiamo bisogno di allocare nuova memoria.
- Se siamo in fase di assegnameto, dobbiamo solo creare una store in una locazione di memoria.
Il flag definition permette di distinguere queste due fasi e quindi la classe genererà un codice diverso in base a "definition"
*/
class InitAST: public RootAST {  
protected:
    const std::string Name;
    bool definition; //definition viene scritto da oggetti di VarBindingAST e AssignmentAST
public:
    InitAST(const std::string Name, bool definition);
    bool isDefinition();
    const std::string& getName() const;
    virtual Value *codegen(driver& drv) override = 0;
}; 

class BindingAST: public InitAST {
public:
    BindingAST(const std::string Name);
public:
    virtual AllocaInst *codegen(driver& drv) override = 0;
};

class VarBindingAST: public BindingAST {
private:
    ExprAST* Val;
public:
    VarBindingAST(const std::string Name, ExprAST* Val);
    AllocaInst *codegen(driver& drv) override;
};

class ArrayBindingAST: public BindingAST {
private:
    double itemNum;
    std::vector<ExprAST*> initExprList;
public:
    ArrayBindingAST(const std::string Name, double itemNum, std::vector<ExprAST*> initExprList = std::vector<ExprAST*>());
    AllocaInst *codegen(driver& drv) override;
};

class AssignmentAST: public InitAST {
public:
    AssignmentAST(const std::string Name);
};

class VarAssignmentAST: public AssignmentAST {
private:
    ExprAST* Val;
public:
    VarAssignmentAST(const std::string Name, ExprAST* Val);
    Value *codegen(driver& drv) override;
};

class ArrayAssignmentAST: public AssignmentAST {
private:
    ExprAST* Idx;
    ExprAST* Val;
public:
    ArrayAssignmentAST(const std::string Name, ExprAST* Val, ExprAST* Idx);
    Value *codegen(driver& drv) override;
};

class PrototypeAST : public RootAST {
private:
    std::string Name;
    std::vector<std::string> Args;
    bool emitcode;

public:
    PrototypeAST(std::string Name, std::vector<std::string> Args);
    const std::vector<std::string> &getArgs() const;
    lexval getLexVal() const override;
    Function *codegen(driver& drv) override;
    void noemit();
};

class FunctionAST : public RootAST {
private:
    PrototypeAST* Proto;
    BlockAST* Body;
    bool external;
  
public:
    FunctionAST(PrototypeAST* Proto, BlockAST* Body);
    Function *codegen(driver& drv) override;
};

#endif // ! DRIVER_HH
