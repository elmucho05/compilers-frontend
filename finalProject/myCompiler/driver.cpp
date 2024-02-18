#include "driver.hpp"
#include "parser.hpp"

// Generazione di un'istanza per ciascuna della classi LLVMContext,
// Module e IRBuilder. Nel caso di singolo modulo è sufficiente
LLVMContext *context = new LLVMContext;
Module *module = new Module("Kaleidoscope", *context);
IRBuilder<> *builder = new IRBuilder(*context);


/*  Utility per la segnalazione di eventuali errori */
Value *LogErrorV(const std::string Str) {
    std::cerr << Str << std::endl;
    return nullptr;
}

static AllocaInst *CreateEntryBlockAlloca(Function *fun, StringRef VarName, Type* T = Type::getDoubleTy(*context)) {
    IRBuilder<> TmpB(&fun->getEntryBlock(), fun->getEntryBlock().begin());
    return TmpB.CreateAlloca(T, nullptr, VarName);
}

driver::driver(): trace_parsing(false), trace_scanning(false) {};

int driver::parse (const std::string &f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    yy::parser parser(*this);
    parser.set_debug_level(trace_parsing);
    int ris = parser.parse();
    scan_end();
    return ris;
}

void driver::codegen() {
    root->codegen(*this);
};

/****************SeqAST************************/
SeqAST::SeqAST(RootAST* first, RootAST* continuation):
    first(first), continuation(continuation) {};

Value *SeqAST::codegen(driver& drv) {
    if (first != nullptr) {
        Value *f = first->codegen(drv);
    }
    else {
        if (continuation == nullptr) return nullptr;
    }
    Value *c = continuation->codegen(drv);
    return nullptr;
};

/**********************StmtAST***********************/
/* Non posso utilizzare SeqAST perché devo ritornare un puntatore al Value della
Funzione chiamante. SeqAST restituisce un nullptr.*/
StmtAST::StmtAST(RootAST* stmt): stmt(stmt) {};

//  Genera solamente il codice dell'istruzione da cui è "composto" lo statement
Value *StmtAST::codegen(driver& drv) {
    return stmt->codegen(drv);
};

/****************GlobalVarAST*****************/
GlobalVarAST::GlobalVarAST(const std::string &Name): Name(Name) {};

lexval GlobalVarAST::getLexVal() const {
    lexval lval = Name;
    return lval;
};

Value *GlobalVarAST::codegen(driver& drv) {
    //prende il tipo della variabile, dicendo con "false" che non è una costante
    //col "commonLinkage" diciamo che possiamo fare riferimeto alla variabile sia da dentro il modulo che fuori
    //infine viene inizializzato il suo valore a 0 col nome Name 
    Value *globalVar = new GlobalVariable(*module, Type::getDoubleTy(*context), false, GlobalValue::CommonLinkage,  ConstantFP::get(*context, APFloat(0.0)), Name);
    globalVar->print(errs());
    fprintf(stderr, "\n");
    return globalVar;
}

/************GlobalArrayAST****************/
GlobalArrayAST::GlobalArrayAST(const std::string &Name, double itemNum): 
    GlobalVarAST(Name), itemNum(itemNum) {};

Value *GlobalArrayAST::codegen(driver& drv) {
    //stesso procedimento della variaible globale
    ArrayType *varType = ArrayType::get(Type::getDoubleTy(*context),itemNum);
    Value *globalVar = new GlobalVariable(*module, varType, false, GlobalValue::CommonLinkage, ConstantAggregateZero::get(varType), Name);
    globalVar->print(errs());
    fprintf(stderr, "\n");
    return globalVar;
}

/*********************NumberExprAST*********************/
NumberExprAST::NumberExprAST(double Val): Val(Val) {};

lexval NumberExprAST::getLexVal() const {
  lexval lval = Val;
  return lval;
};

//genero soltanto una costante LLVM IR corrispondente al valore float memorizzato nel nodo, non un'istruzione
Value *NumberExprAST::codegen(driver& drv) {  
    return ConstantFP::get(*context, APFloat(Val));
};

/********************VariableExprAST********************/
VariableExprAST::VariableExprAST(const std::string &Name): Name(Name) {};

lexval VariableExprAST::getLexVal() const {
    lexval lval = Name;
    return lval;
};

Value *VariableExprAST::codegen(driver& drv) {
    AllocaInst *A = drv.NamedValues[Name];
    Type *varType;
    
    if (A){
        varType = A->getAllocatedType();
        if(varType->isArrayTy())
            return LogErrorV("SyntaxError, un array va usato con le quadre []");
        //se non è un'array, genera una load ritornado il valore
        return builder->CreateLoad(varType, A, Name.c_str());
    }
    else{
        //idem per la globale
        GlobalVariable* globalVar = module->getNamedGlobal(Name);
        if(globalVar){
            varType = globalVar->getValueType();
            if(varType->isArrayTy()) //controllo se è un'array
                return LogErrorV("SyntaxError, un array va usato con le quadre []");
            return builder->CreateLoad(varType, globalVar, Name.c_str());
        }
    }
    return LogErrorV("Variabile "+Name+" non definita");
}

/********************ArrayExprAST********************/
//"id" "[" exp "]"      { $$ = new ArrayExprAST($1,$3); };        
ArrayExprAST::ArrayExprAST(const std::string &Name, ExprAST* Idx): 
    Name(Name), Idx(Idx) {};

lexval ArrayExprAST::getLexVal() const {
    lexval lval = Name;
    return lval;
};

Value *ArrayExprAST::codegen(driver& drv) {

    Type *varType;
    Value *array = drv.NamedValues[Name];
    // controllo se è un array
    //come nelle variabili, viene data la precedenza alle var locali
    if (array){
        varType = drv.NamedValues[Name]->getAllocatedType();
        if(!varType->isArrayTy())
            return LogErrorV("La variabile locale " + Name + " non è un array");
    }
    else{
        GlobalVariable* globalVar = module->getNamedGlobal(Name);
        if(globalVar){
            varType = globalVar->getValueType();
            if(!varType->isArrayTy())
                return LogErrorV("La variabile globale " + Name + " non è un array");
            array = globalVar;
        }
        else{
            return LogErrorV("Variabile "+Name+" non definita");
        }
    }
    
    //comincio a generare codice partendo dall'index
    Value *indexVal = Idx->codegen(drv);
    if (!indexVal)
        return nullptr;

    //come indicato nelle slide, va convertito l'inidice in Int32
    indexVal = builder->CreateFPToSI(indexVal, Type::getInt32Ty(*context), "indexinitalize");

    ArrayType *AT = dyn_cast<ArrayType>(varType);

    Value *cell = builder->CreateInBoundsGEP(AT, array, {ConstantInt::get(Type::getInt32Ty(*context), 0), indexVal});
    return builder->CreateLoad(Type::getDoubleTy(*context), cell, Name.c_str());
}

/********************BinaryExprAST**********************/
BinaryExprAST::BinaryExprAST(char Op, ExprAST* LHS, ExprAST* RHS):
    Op(Op), LHS(LHS), RHS(RHS) {};

Value *BinaryExprAST::codegen(driver& drv) {
    Value *L = LHS->codegen(drv);
    Value *R = RHS->codegen(drv);
    if (!L || !R) 
        return nullptr;
    switch (Op) {
    case '+':
        return builder->CreateFAdd(L,R,"addres");
    case '-':
        return builder->CreateFSub(L,R,"subres");
    case '*':
        return builder->CreateFMul(L,R,"mulres");
    case '/':
        return builder->CreateFDiv(L,R,"addres");
    case '<':
        return builder->CreateFCmpULT(L,R,"lttest");
    case '=':
        return builder->CreateFCmpUEQ(L,R,"eqtest");
    case '&':
        return builder->CreateAnd(L,R,"andres");
    case '|':
        return builder->CreateOr(L,R,"orres");
    default:  
        std::cout << Op << std::endl;
        return LogErrorV("Operatore binario non supportato");
    }
};

/*****************UnaryExprAST********************/
UnaryExprAST::UnaryExprAST(char Op, ExprAST* Val):
    Op(Op), Val(Val) {};

Value *UnaryExprAST::codegen(driver& drv) {
    Value *Operand = Val->codegen(drv);
    if (!Operand) 
        return nullptr;
    switch (Op) {
    case '!':
        return builder->CreateNot(Operand,"notres");
    default:  
        std::cout << Op << std::endl;
        return LogErrorV("Operatore unario non supportato");
    }
};
/**********CallExprAST************/
CallExprAST::CallExprAST(std::string Callee, std::vector<ExprAST*> Args):
    Callee(Callee),  Args(std::move(Args)) {};

lexval CallExprAST::getLexVal() const {
    lexval lval = Callee;
    return lval;
};

Value* CallExprAST::codegen(driver& drv) {
    /*  Viene cercata la funzione col nome specificato da Callee, se non esiste si ha un errore */
    Function *CalleeF = module->getFunction(Callee);
    if (!CalleeF)
        return LogErrorV("Funzione non definita");

    if (CalleeF->arg_size() != Args.size())
        return LogErrorV("Numero di argomenti non corretto");

    std::vector<Value *> ArgsV;
    for (auto arg : Args) {
        ArgsV.push_back(arg->codegen(drv));
        if (!ArgsV.back())
            return nullptr;
    }
    return builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

/*************************IfExprAST*************************/
IfExprAST::IfExprAST(ExprAST* Cond, ExprAST* TrueExp, ExprAST* FalseExp):
    Cond(Cond), TrueExp(TrueExp), FalseExp(FalseExp) {};
   
Value* IfExprAST::codegen(driver& drv) {
    Value* CondV = Cond->codegen(drv);
    if (!CondV)
        return nullptr;
    // Ora bisogna generare l'istruzione di salto condizionato, ma prima
    // vanno creati i corrispondenti basic block nella funzione attuale
    // (ovvero la funzione di cui fa parte il corrente blocco di inserimento)
    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *TrueBB =  BasicBlock::Create(*context, "trueexp", function);
    // Il blocco TrueBB viene inserito nella funzione dopo il blocco corrente

    BasicBlock *FalseBB = BasicBlock::Create(*context, "falseexp");
    BasicBlock *MergeBB = BasicBlock::Create(*context, "endcond");
  
    // Gli altri due blocchi non vengono ancora inseriti perché le istruzioni
    // previste nel "ramo" true del condizionale potrebbe dare luogo alla creazione
    // di altri blocchi, che naturalmente andrebbero inseriti prima di FalseBB
    
    // Ora possiamo crere l'istruzione di salto condizionato
    builder->CreateCondBr(CondV, TrueBB, FalseBB);
    
    // genero il codice relativo al ramo true
    builder->SetInsertPoint(TrueBB);
    Value *TrueV = TrueExp->codegen(drv);
    if (!TrueV)
        return nullptr;
    //branch indondizionata al blocco merge
    builder->CreateBr(MergeBB);
    
    //la codegen del ramo true potrebbe aver inserito altri blocchi quindi in questo modo 
    // recupero il blocco corrente
    TrueBB = builder->GetInsertBlock();

    //inserimento blocco del ramo false
    function->insert(function->end(), FalseBB);
    
    //genero il codice del ramo false
    builder->SetInsertPoint(FalseBB);
    Value *FalseV = FalseExp->codegen(drv);
    if (!FalseV)
        return nullptr;
    builder->CreateBr(MergeBB);
    
    //recupero il blocco poiché la codegen potrebbe aver generato altri blocchi
    FalseBB = builder->GetInsertBlock();

    //inserimento blocco del ramo merge
    function->insert(function->end(), MergeBB);
    

    builder->SetInsertPoint(MergeBB);

    //creazione nodo PHI per riunire i flussi
    PHINode *PN = builder->CreatePHI(Type::getDoubleTy(*context), 2, "condval");
    PN->addIncoming(TrueV, TrueBB);
    PN->addIncoming(FalseV, FalseBB);
    return PN;
};

/*************************IfStmtAST*************************/
IfStmtAST::IfStmtAST(ExprAST* Cond, StmtAST* TrueStmt, StmtAST* FalseStmt):
    Cond(Cond), TrueStmt(TrueStmt), FalseStmt(FalseStmt) {};

Value* IfStmtAST::codegen(driver& drv) {
    Value* CondV = Cond->codegen(drv);
    if (!CondV)
        return nullptr;
    
    // Ora bisogna generare l'istruzione di salto condizionato, ma prima
    // vanno creati i corrispondenti basic block nella funzione attuale
    // (ovvero la funzione di cui fa parte il corrente blocco di inserimento)
    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *TrueBB =  BasicBlock::Create(*context, "trueexp", function);
    // Il blocco TrueBB viene inserito nella funzione dopo il blocco corrente

    //il blocco false viene generato solo se è effettivamente presente il ramo false dell'if
    BasicBlock *FalseBB;
    if(FalseStmt)
        FalseBB = BasicBlock::Create(*context, "falseexp");

    BasicBlock *MergeBB = BasicBlock::Create(*context, "endcond");
    // Gli altri due blocchi non vengono ancora inseriti perché le istruzioni
    // previste nel "ramo" true del condizionale potrebbe dare luogo alla creazione
    // di altri blocchi, che naturalmente andrebbero inseriti prima di FalseBB
    
    // L'istruzione di salto condizionato tiene conto dell'eventuale assenza del ramo false
    if(FalseStmt)
        builder->CreateCondBr(CondV, TrueBB, FalseBB);
    else
        // se il false non è presente le due strade possibili saranno true e merge
        builder->CreateCondBr(CondV, TrueBB, MergeBB);

    // generazione codice per il ramo true     
    builder->SetInsertPoint(TrueBB);
    Value *TrueV = TrueStmt->codegen(drv);
    if (!TrueV)
        return nullptr;
    builder->CreateBr(MergeBB);
    
    // dobbiamo ancora tenere conto che potrebbero essere stati generati altri blocchi 
    // recuperiamo quello corrente
    TrueBB = builder->GetInsertBlock();

    //se il ramo false non è presente non viene generato codice
    Value *FalseV;
    if(FalseStmt){
        function->insert(function->end(), FalseBB);
        // genero codice per il false        
        builder->SetInsertPoint(FalseBB);
        FalseV = FalseStmt->codegen(drv);
        if (!FalseV)
            return nullptr;
        builder->CreateBr(MergeBB);
        
        // dobbiamo ancora tenere conto che potrebbero essere stati generati altri blocchi, 
        // recuperiamo quello corrente
        FalseBB = builder->GetInsertBlock();
    }

    function->insert(function->end(), MergeBB);
    
    // Ora possiamo cominciare a generare codice per la renuion dei flussi
    builder->SetInsertPoint(MergeBB);

    // Diversamente da IfEXpr, se il costrutto è True, il valore finale dello statement è già calcolato dal ramo True
    // Sennò devo genrare codice un istruzione PHI
    if(FalseStmt){
        PHINode *PN = builder->CreatePHI(Type::getDoubleTy(*context), 2, "condval");
        PN->addIncoming(TrueV, TrueBB);
        PN->addIncoming(FalseV, FalseBB);
        return PN;
    }
    else{
        return TrueV;
    }
};

/*********************ForStmtAST***********************/
ForStmtAST::ForStmtAST(InitAST* Init, ExprAST* Cond, RootAST* Assignment, StmtAST* Stmt):
    Init(Init), Cond(Cond), Assignment(Assignment), Stmt(Stmt) {};

Value* ForStmtAST::codegen(driver& drv) {
    // "for" "(" init ";" condexp ";" assignment ")" 
    /*
    Possiamo dividere il processo di generazione del codice per il ciclo in 4 fasi:
    1. definizione o assegnamento di una variabile su cui iterare. (int i=0 oppure  i=0)
    2. parte della condizione (i<10), se è vera, allora si entra nel loop.
    3. blocco delle istruzioni da eseguire dentro al for. Alla fine si fa un salto incondizionato al blocco condizione
    4. Da dove riprende il flusso del programma una volta terminata l'esecuzione del for.
    */
    BasicBlock *MergeBB = BasicBlock::Create(*context, "endloop");

    //------- 1. definizione o assegnamento di una variabile su cui iterare. (int i=0 oppure  i=0) --------//

    // questa map viene utilizzata nel caso ci sia una definizione per oscurare eventuali variabili con lo stesso nome
    // int i=3
    //for int i=1;
    //Usato per salvare il valore di una entry nella symbol table
    std::map<std::string, AllocaInst*> AllocaTmp;
    if(!Init->isDefinition()){
        //generazione codice assegnamento variabile, non rimane nient'altro da fare
        if(!Init->codegen(drv)) return nullptr;
    }
    else{
        // Stiamo trattando il caso in cui dobbiamo allocare nuova memoria. Dobbiamo assolutamente tenere in considerazione che
        // la nuova variabile che stiamo definiendo potrebbe essere già stata definita con lo stesso nome, in quel caso dobbiamo
        // offuscare la dichiarazione precedente nella symbol table.
        // Essendo che la codegen ritorna un Value, dobbiamo castare il risultato il AllocaInst. Facendo così, possiamo inserire il valore
        // temporaneo nella symbol table. 
        AllocaInst *initVal = dyn_cast<AllocaInst>(Init->codegen(drv));
        if(!initVal) return nullptr;

        AllocaTmp[Init->getName()] = drv.NamedValues[Init->getName()];
        drv.NamedValues[Init->getName()] = initVal;
    }

    //----- 2. parte della condizione (i<10), se è vera, allora si entra nel loop. ----//

    // Creazione blocco per valutare la condizione, si salterà a questo blocco alla fine di ogni iterazione
    // E' il primo blocco ad essere eseguito quindi viene agganciato alla fine della funzione e posiziono il builder
    // al suo interno 
    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *CondBB =  BasicBlock::Create(*context, "condeval", function);

    // Una volta generato il blocco viene inserito un salto incondizionato proveniente dal blocco precedente per
    // permettere di "entrare" concettualmente nella fase di esecuzione vera e propria del for
    builder->CreateBr(CondBB);

    // Ora si posiziona il builder all'interno del blocco di valutazione della condizione
    builder->SetInsertPoint(CondBB);

    /*  Creazione blocco loop, viene lasciato sconnesso momentaneamente in attesa che venga generato il codice
        per la valutazione della condizione */
    BasicBlock *ForBB =  BasicBlock::Create(*context, "forloop");

    //generazione codice per valutazione condizione (la condizione viene valutata all'inizio di ogni iterazione)
    Value* CondV = Cond->codegen(drv);
    if (!CondV)
        return nullptr;

    //generazione codice per salto condizionato
    builder->CreateCondBr(CondV, ForBB, MergeBB);
    
    //---- istruzioni da eseguire in Loop -------//    
    //viene agganciato il blocco che gestisce il loop creato precedentemente
    function->insert(function->end(), ForBB);
    builder->SetInsertPoint(ForBB);

    //generazione codice del body interno al loop e return nullptr se ci sono stati errori
    if(!Stmt->codegen(drv))
        return nullptr;
    
    //serve a recuperare il blocco corrente nel caso siano stati generati altri blocchi da stmt->codegen
    builder->GetInsertBlock();
    
    //generazione codice dell'assegnamento finale e return nullptr se ci sono stati errori
    Value *var = Assignment->codegen(drv);
    if(!var)
        return nullptr;

    //salto incondizionato a blocco Cond per effettuare una nuova verifica della condizione del loop
    builder->CreateBr(CondBB);

    //-----usciata dal loop e da dove ripredere il programma ----//
    //viene agganciato il blocco di uscita dal loop e si posiziona il builder al suo interno
    function->insert(function->end(), MergeBB);
    builder->SetInsertPoint(MergeBB);

    // viene reinserita nella NamedValues la variabile che prima era stata offuscata da un'eventuale definizione

    if(Init->isDefinition())
        drv.NamedValues[Init->getName()] = AllocaTmp[Init->getName()];

    // viene restituita una costante pari a zero per indicare che non c'è stato nessun errore
    return ConstantFP::get(*context, APFloat(0.0));
}

/*******************BlockAST********************/
BlockAST::BlockAST(std::vector<BindingAST*> Def, std::vector<StmtAST*> Stmts): 
         Def(std::move(Def)), Stmts(std::move(Stmts)) {};

Value* BlockAST::codegen(driver& drv) {
    
    //implementazione meccanismo di offuscamento variabili
    std::vector<AllocaInst*> AllocaTmp;
    for (int i=0, e=Def.size(); i<e; i++) {
        // Per ogni definizione di variabile si genera il corrispondente codice che
        // (in questo caso) non restituisce un registro SSA ma l'istruzione di allocazione
        AllocaInst *boundval = Def[i]->codegen(drv);
        if (!boundval) 
            return nullptr;
        // Viene temporaneamente rimossa la precedente istruzione di allocazione
        // della stessa variabile (nome) e inserita quella corrente
        AllocaTmp.push_back(drv.NamedValues[Def[i]->getName()]);
        drv.NamedValues[Def[i]->getName()] = boundval;
    };

    /*  Generazione del codice relativo ai vari statement, ad ogni generazione viene controllato
        se è stato restituito un puntatore nullo in modo da segnalare eventuali errori  */
    Value *blockvalue;
    for(int i=0, s=Stmts.size(); i<s; i++){
        blockvalue = Stmts[i]->codegen(drv);
        if(!blockvalue) return nullptr;
    }
        
    // Prima di uscire dal blocco, si ripristina lo scope esterno al costrutto
    for (int i=0, e=Def.size(); i<e; i++) {
            drv.NamedValues[Def[i]->getName()] = AllocaTmp[i];
    };
    
    /*  Il valore di ritorno del blocco corrisponde all'ultimo registro SSA definito da uno statement */
    return blockvalue;
};

/*****************InitAST************************/

InitAST::InitAST(const std::string Name, bool definition):
    Name(Name), definition(definition) {};

bool InitAST::isDefinition(){
    return definition;
}

const std::string& InitAST::getName() const { 
   return Name; 
};

/*******************BindingAST*************************/

BindingAST::BindingAST(const std::string Name):
    InitAST(Name, true) {};

/********************VarBindingAST***********************/
VarBindingAST::VarBindingAST(const std::string Name, ExprAST* Val):
    BindingAST(Name), Val(Val) {};
AllocaInst* VarBindingAST::codegen(driver& drv) {
    Function *fun = builder->GetInsertBlock()->getParent();
    Value *BoundVal = Val->codegen(drv);
    if (!BoundVal)
        return nullptr;
    AllocaInst *Alloca = CreateEntryBlockAlloca(fun, Name);
    builder->CreateStore(BoundVal, Alloca);
    
    return Alloca;
};

/*****************ArrayBingingAST************************/
ArrayBindingAST::ArrayBindingAST(const std::string Name, double itemNum, std::vector<ExprAST*> initExprList):
    BindingAST(Name), itemNum(itemNum), initExprList(std::move(initExprList)) {};

AllocaInst* ArrayBindingAST::codegen(driver& drv) {
    Function *fun = builder->GetInsertBlock()->getParent(); 
    ArrayType *AT = ArrayType::get(Type::getDoubleTy(*context),itemNum);

    AllocaInst *Alloca = CreateEntryBlockAlloca(fun, Name, AT); //alloco memoria

    if(itemNum != initExprList.size() && initExprList.size()!=0){
        //controllo sul numero di elementi con cui è sato dichiarato l'array
        LogErrorV("Array con " + std::to_string(itemNum) + " elementi inizializzato con " + std::to_string(initExprList.size()) + " espressioni");
        return nullptr; 
    }

    for(int i = 0; i < initExprList.size(); i++){
        Value *exprRes = initExprList[i]->codegen(drv);
        if(!exprRes) 
            return nullptr;
        Value *index = ConstantInt::get(*context, APInt(32, i, true));
        Value *cell = builder->CreateInBoundsGEP(AT, Alloca, {ConstantInt::get(Type::getInt32Ty(*context), 0), index});
        builder->CreateStore(exprRes, cell);
    }
    
    return Alloca;
};

/******************AssignmentAST*********************/
AssignmentAST::AssignmentAST(const std::string Name):
    InitAST(Name, false) {};

/*****************VarAssignmentAST***********************/
VarAssignmentAST::VarAssignmentAST(const std::string Name, ExprAST* Val):
   AssignmentAST(Name), Val(Val) {};

Value* VarAssignmentAST::codegen(driver& drv) {
    //priorità a variabili locali, se un nome non è definito tra le variabili locali allora si passa 
    //a controllare le variabili globali
    Value *var = drv.NamedValues[Name];
    Type *varType;
    if (var){
        varType = drv.NamedValues[Name]->getAllocatedType();
    }
    else{
        GlobalVariable *globalVar = module->getNamedGlobal(Name);
        if(!globalVar)
            return LogErrorV("Variabile "+Name+" non definita");
        varType = globalVar->getValueType();
        var = globalVar;       
    }

    //controllo per verificare che la variabile non sia in realtà un array
    if(varType->isArrayTy())
        return LogErrorV("Array utilizzato senza operatore []");

    
    // Ora viene generato il codice che definisce il valore della variabile
    Value *BoundVal = Val->codegen(drv);
    if (!BoundVal)  // Qualcosa è andato storto nella generazione del codice?
        return nullptr;
    // ... e si genera l'istruzione per memorizzarvi il valore dell'espressione,
    // ovvero il contenuto del registro BoundVal
    builder->CreateStore(BoundVal, var);

    /*  Viene restituito un registro SSA che contiene il valore del registro (o della variabile globale) in cui è stata fatta
        la store. Questo viene fatto per ritornare sempre un valore double (dato che altrimenti, ritornando direttamente
        il registro o la variabile globale si avrebbe un valore di tipo puntatore). Tutte le funzioni si aspettano un tipo di ritorno double
        quindi questa scelta si rende necessaria */
    return builder->CreateLoad(varType, var, ("ret_" + Name).c_str());
};

/****************ArrayAssignmentAST******************/
ArrayAssignmentAST::ArrayAssignmentAST(const std::string Name, ExprAST* Idx, ExprAST* Val):
   AssignmentAST(Name), Idx(Idx), Val(Val) {};

Value* ArrayAssignmentAST::codegen(driver& drv) {

    Type *varType;
    Value *array = drv.NamedValues[Name]; //controllo sempre prima le var locali
    if(array){
        varType = drv.NamedValues[Name]->getAllocatedType();
    }
    else{
        GlobalVariable* globalArray = module->getNamedGlobal(Name);
        if(globalArray){
            varType = globalArray->getValueType();
            array = globalArray;
        }
        else{
            return LogErrorV(Name+" non definito");  
        }
    }
    if(!varType->isArrayTy())
        return LogErrorV("un array deve avere il []");

    Value *indexVal = Idx->codegen(drv);
    if (!indexVal) 
        return nullptr;

    //converto da double a int
    indexVal = builder->CreateFPToSI(indexVal, Type::getInt32Ty(*context), "intindex");

    Value *BoundVal = Val->codegen(drv);
    if (!BoundVal)
        return nullptr;

    ArrayType *AT = dyn_cast<ArrayType>(varType);
    Value *cell = builder->CreateInBoundsGEP(AT, array, {ConstantInt::get(Type::getInt32Ty(*context), 0), indexVal});
    builder->CreateStore(BoundVal, cell);
    return builder->CreateLoad(AT->getElementType(), cell, ("ret_" + Name).c_str());
};

/*************PrototypeAST*********************/
PrototypeAST::PrototypeAST(std::string Name, std::vector<std::string> Args):
    Name(Name), Args(std::move(Args)), emitcode(true) {};  //Di regola il codice viene emesso

lexval PrototypeAST::getLexVal() const {
    lexval lval = Name;
    return lval;	
};

const std::vector<std::string>& PrototypeAST::getArgs() const { 
    return Args;
};

void PrototypeAST::noemit() { 
    emitcode = false; 
};

Function *PrototypeAST::codegen(driver& drv) {
    // Costruisce una struttura, qui chiamata FT, che rappresenta il "tipo" di una
    // funzione. Con ciò si intende a sua volta una coppia composta dal tipo
    // del risultato (valore di ritorno) e da un vettore che contiene il tipo di tutti
    // i parametri. Si ricordi, tuttavia, che nel nostro caso l'unico tipo è double.
    
    // Prima definiamo il vettore (qui chiamato Doubles) con il tipo degli argomenti
    std::vector<Type*> Doubles(Args.size(), Type::getDoubleTy(*context));
    // Quindi definiamo il tipo (FT) della funzione
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(*context), Doubles, false);
    // Infine definiamo una funzione (al momento senza body) del tipo creato e con il nome
    // presente nel nodo AST. ExternalLinkage vuol dire che la funzione può avere
    // visibilità anche al di fuori del modulo
    Function *F = Function::Create(FT, Function::ExternalLinkage, Name, *module);

    // Ad ogni parametro della funzione F (che, è bene ricordare, è la rappresentazione 
    // llvm di una funzione, non è una funzione C++) attribuiamo ora il nome specificato dal
    // programmatore e presente nel nodo AST relativo al prototipo
    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(Args[Idx++]);
    if (emitcode) {
        F->print(errs());
        fprintf(stderr, "\n");
    };
    
    return F;
}

/****************FunctionAST*************************/
FunctionAST::FunctionAST(PrototypeAST* Proto, BlockAST* Body): Proto(Proto), Body(Body) {};

Function *FunctionAST::codegen(driver& drv) {
    Function *function = 
    module->getFunction(std::get<std::string>(Proto->getLexVal()));
    if (!function)
        function = Proto->codegen(drv); //genera non emmettere ancora
    else
        return nullptr;
    if (!function)
        return nullptr;  

    // Altrimenti si crea un blocco di base in cui iniziare a inserire il codice
    BasicBlock *BB = BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(BB);
    
    for (auto &Arg : function->args()) {
        // Genera l'istruzione di allocazione per il parametro corrente
        AllocaInst *Alloca = CreateEntryBlockAlloca(function, Arg.getName());
        // Genera un'istruzione per la memorizzazione del parametro nell'area
        // di memoria allocata
        builder->CreateStore(&Arg, Alloca);
        // Registra gli argomenti nella symbol table per eventuale riferimento futuro
        drv.NamedValues[std::string(Arg.getName())] = Alloca;
    } 
    
    // Ora può essere generato il codice corssipondente al body (che potrà
    // fare riferimento alla symbol table)
    if (Value *RetVal = Body->codegen(drv)) {
        builder->CreateRet(RetVal);

        verifyFunction(*function);
        function->print(errs());
        fprintf(stderr, "\n");
        return function;
    }

    function->eraseFromParent();
    return nullptr;
};

