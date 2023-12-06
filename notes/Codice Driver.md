Dopo aver costruito l'AST, allegare dei nodi per generare il relativo costrutto. Abbiamo

1. un main
2. un parser
3. uno scanner
4. un driver


La generazione del codice è a parte, prima genero l'AST e poi lo visito così posso generare codice intermedio. 

Nel file `parser.yy`:
```bison
definition: "def" proto expr { $2-> noemit()}
```

il `noemit()` dice di non generare codice. Siccome è applicato al secondo parametro (`proto`) significa fa parte della classe "proto"

Nello scanner non ho cambiato nulla.

Nel file **driver.hpp** abbiamo:

#### Driver.hpp

Contiene anche tutte le classi per i vari costrutti.
- classe driver, che creiamo perché dobbiamo passarle il contesto. 
	- questa classe contiene una `map`, tabella associativa chiave valore e la chiama `NamedValues`. 
	- la linea `static inline Ctn` la possimo togliere
	- `RootAST* root` : dichiarazione della radice alla quale ci scrive il parser.
	- `int parse(const std::string &f)` prende in input il file da cui legere
	- `bool trace_parsing` semplicemente per il debug
	- `void scan_end() scan_begin()` 
	- `yy::location location;` usata dallo scanner per localizzare i token
	- `void codegen()` funzione generatrice del codice, ogni classe avrà la sua relativa, la classe delle espressioni, genera codice per le espressioni. 
	- std::variant <> lexval , l'abbiamo visto in classe.


#### Driver.cpp 
Implementazione della classe driver.

Ci servono oggetti di 3 classi particolari:
1. **LLVMContext** : classe opaca che contiene tutte le strutture dati importanti per generare codice
2. **Module**
3. **IRBuilder** : metodi che generano internamente rappresentazioni di tutte le istruzioni, poi ad un certo punto le possiamo emettere. Costruiscono quindi quindi le varie istruzioni del codice intermedio. 

implementazioni delle funzioni 

```cpp
//Implementazione del metodo parse

int driver::parse (const std::string &f) {

file = f; // File con il programma

location.initialize(&file); // Inizializzazione dell'oggetto location passandoli il file, siamo posizionati su riga 0, colonna 0

scan_begin(); // Inizio scanning (ovvero apertura del file programma), apertura del file

yy::parser parser(*this); // Istanziazione del parser, cioè passandoli l'oggetto driver.

parser.set_debug_level(trace_parsing); //Set del Livello di debug del parsed

int res = parser.parse(); // Chiamata dell'entry point del parser
//chiamo il parser
scan_end(); // Fine scanning (ovvero chiusura del file programma)
//chiusura del file

return res;
// questp è solo un risultato 0 se è andato tutto bene. 
}
```


###### Funzione codegen();
cominicio a generare codice dalla radice
```cpp
void driver::codegen() {
root->codegen(*this);
};
```


#### I signoli costrutti
```cpp
SeqAST::SeqAST(RootAST* first, RootAST* continuation):

first(first), continuation(continuation) {};

  
// La generazione del codice per una sequenza è banale:

// mediante chiamate ricorsive viene generato il codice di first e

// poi quello di continuation (con gli opportuni controlli di "esistenza")

Value *SeqAST::codegen(driver& drv) {
//se il first è != da nullptr
if (first != nullptr) {

Value *f = first->codegen(drv);
// tutte le codegen restituiscono  un oggetto lexvalue(forse)
} else {

if (continuation == nullptr) return nullptr;
//se first è nullptr, guardo anche se continuation lo è
}
//i ogni caso, esco, prendo codegen, calcolo codegen di destr ricorsivamente.
Value *c = continuation->codegen(drv);

return nullptr;

};
```

Si scende a sx, genera il codice, il risultato calcolato viene rappresentato da un registro : `Value *f ` è un registro *SSA* (Stati single Access)
- un registro che può essere scritto solo da un'istruzione, ma allo stesso tempo, se l'istruzione è eseguita più volte, essa può riscrivere più volte quel registro.

#### Binary expression Tree
Se mi trovo un nodo che è un operatore binario. 
```cpp
BinaryExprAST::BinaryExprAST(char Op, ExprAST* LHS, ExprAST* RHS):
Op(Op), LHS(LHS), RHS(RHS) {};

// La generazione del codice in questo caso è di facile comprensione.

// Vengono ricorsivamente generati il codice per il primo e quello per il secondo

// operando. Con i valori memorizzati in altrettanti registri SSA si

// costruisce l'istruzione utilizzando l'opportuno operatore

Value *BinaryExprAST::codegen(driver& drv) {

Value *L = LHS->codegen(drv); //genera il codice che lascia il risultato in un registro chiamato L

Value *R = RHS->codegen(drv); //genera il codice e salva risultato in R 

if (!L || !R) //se uno solo è null, ritorna nulla

	return nullptr;

switch (Op) { //altrimenti controllo l'operatore memorizzato nel nodo

	case '+':
	//chiamo il builder che ha sto metodo e opzionalmente il nome di un regsitro in cui mettere il risultato
	return builder->CreateFAdd(L,R,"addres"); //add res, risultato somma
	
	case '-':
	
	return builder->CreateFSub(L,R,"subres");
	
	case '*':
	
	return builder->CreateFMul(L,R,"mulres");
	
	case '/':
	
	return builder->CreateFDiv(L,R,"addres");
	
	default:

std::cout << Op << std::endl;

return LogErrorV("Operatore binario non supportato");

}

};
```



Andiamo ora ad analizzare   
##### NumberExprAST
Cosa deve fare la codgen per un number? A un number non corrisponde un'istruzione, perché un numero è una costante. 

```c++
NumberExprAST::NumberExprAST(double Val): Val(Val) {};

lexval NumberExprAST::getLexVal() const {

// Non utilizzata, Inserita per continuità con versione precedente

lexval lval = Val;

return lval;

};

/*
non posso scrivere direttamente return val, anche se codegen riece a vedere l'attributo. 

- questo perché le costanti devono essere uniche e sono mantenute tutte da questo contesto. Nel contest sono rappresentate nel Conetext in modo unico. 
- Quindi fai la get del contesto
	- esempio 3+2, abbiamo le costanti 3 e 2
		- lui si chiede, il 3 è già stato generato?
		- per questo c'è una tabella hash che contiene il contesto
		
*/
Value *NumberExprAST::codegen(driver& drv) {
// se esiste la costante 3(numero 3) nel contest, dammela con get, altrimenti la crei e dammi il puntatore a quella

//devi anche metterci la rappresentazione floating point con APFloat() perché il parser non sai che rappresentazione usa rispetto a llvm? Per questo usiamo la notazione FloatingPoint che ci aiuta a normalizzare le notazini
return ConstantFP::get(*context, APFloat(Val));

};
```

Ci rimangono funzioni e variabili:

#### Generazione codice per Variabili
fa uso di questa funzione
```cpp
//crea una tabella che ad ogni variabile associa un'istruzione 
	//istruzione che alloca un double e restituisce in un registro SSA il puntatore a questa zona di memoria. 


//double x=4, un'istruzione che alloca 8 byte e restituisce il puntatore agli 8 bytee

//Crea un blocco di memoria, il tipo è AllocaInst, prende in input una funzione(*fun) e il nome della variabile(VarName).

// *fun è un oggetto Function LLVM, cioè la rappresentazione in LLVM di una funzione.

//questa funzione cosa fa:
static AllocaInst *CreateEntryBlockAlloca(Function *fun, StringRef VarName) {

//definisco un builder temporaneo per non interagire con quello principale che tiene traccia di dove il codice è stato scritto:

	// questo builder temporaneo, RICORDARE CHE UNA FUNZIONE È FATTA DI BASIC BLOCKS E FINISCE CON SALTO AD ALTRI BLOCKS
	//TmB () accetta in input l'entrypoint, il blocco dove comincia una fuzione
IRBuilder<> TmpB(&fun->getEntryBlock(), fun->getEntryBlock().begin());

//essendo un Builder, abbiamo il metodo CreateAlloca che restitusice una funzione di allocazione
	// Se la variabile
return TmpB.CreateAlloca(Type::getDoubleTy(*context), nullptr, VarName);

//restituisce il puntatore alla zona di memoria
//questa funzione è utile in alcuni casi, fa da utility
}
```


Quando ho x+2
- il parser crea un albero con root +, e figli x e 2
	- come prendo il valore di x? :

```cpp
Value *VariableExprAST::codegen(driver& drv) {
//istruzione : x+2
//accedo alla tabella dei simboli
AllocaInst *A = drv.NamedValues[Name];
//Naped vlaues ha per ogni valore, un'istruzione di allocazione, quindi qua creo un istruzione e la chiamo A

//se nella tabella, non hai trovato quell'istruzione, errore
if (!A)//ho trovato un errore semantico, cioè stai usando una variabile non definita
	return LogErrorV("Variabile non definita");

// prendi e crea un load di (quanto spazio allocare, tabella, e il nome dell'istruzione)
//la load serve per caricare il contenuto di una variabile
return builder->CreateLoad(A->getAllocatedType(), A, Name.c_str());

}
```


Esempio `def F(x) x+1;`
`./kcomp F.k` ti dà la rappresentazione intermedia.

- Alloca un double e mette nel registro SSA x1, di scrittura una sola volta, il puntatore alla zona di memoria
- load : %x2 , load double, ptr %x1, align 8
	- Fai una load in x2 di un double di un valore puntato da x1.
	- `return builder->CreateLoad(A->getAllocatedType(), A, Name.c_str());

Carico il valore di una variabile in un registro. 


Ci manca per poter fare le espressioni, la chiamata di funzione:
#### CalleExprTree
La funzione per poter essere chiamata, deve essere stata dichiarata da qualche parte o come external. 

```c++
Value* CallExprAST::codegen(driver& drv) {

//vado nel nodo che ta nel modulo. 
// nel modulo esiste una funzione già definita di nome Calle? Se sì salvo la sua rappresentazione della funzione dentro la variabile CalleF
Function *CalleeF = module->getFunction(Callee);

if (!CalleeF)

	return LogErrorV("Funzione non definita");

//faccio un ulteriore controllo semantico sul numero di argomenti. Siccome è una grammatica Context-free, possiamo chiamare funzioni di più parametri di quelli dichiarati ma concettualemte e sematicamente non è corretto.
if (CalleeF->arg_size() != Args.size())

	return LogErrorV("Numero di argomenti non corretto");

//Value è un tipo di registro SSA
//costruisco un vettore di oggetti di tipo value
std::vector<Value *> ArgsV;
for (auto arg : Args) { //per ogni argomento passato alla funzione, gli argomenti sono di tipo double, potevo fare double arg in Args
	//mette in fondo al vettore il codice corrispondente a quel argomento.
	ArgsV.push_back(arg->codegen(drv));
	//se non sono arrivato in fondo, errore
	if (!ArgsV.back())
		return nullptr;
	}
//alla fine di questo ciclo for abbiamo ricorsivamente scritto il codice per valutare gli argomenti e tutti questi sono stati messi in un vettore di registri SSA chiamati ArgsV

//Do la chiamata, il numero di argomenti e "calltmp" è il nome del registro SSA dove metto il risultato della chiamata.

return builder->CreateCall(CalleeF, ArgsV, "calltmp");
}
```


Per completare questo linguaggio dobbiamo gestire la definizione di funzione e l'external. 

#### External
vediamo subito la codegen di PrototypeAST:
```c++
//ricordarsi quando ci aspettiamo un protopito
	//se prima ho def proto, mi aspetto un body
	//sennò niente body
Function *PrototypeAST::codegen(driver& drv) {

//Abbiamo il nome di una funzione e il numero di parametri 

//se una funzione ha N argomenti, il suo tipo è N+1 tipi.

//Semplicemente crea un vettore di Tipi che chiamo Double e il tipo di questo è dato trami getDoubleType() che resituiscre la rappresentazione unica di double 
std::vector<Type*> Doubles(Args.size(), Type::getDoubleTy(*context));

//Doubles è un vettore di tipo double ora che contiene i tipi di parametri.

//genera FT (function type) e vado a vedere se esiste un tipo già fatto così sennò lo genero, genero la Function Type
FunctionType *FT = FunctionType::get(Type::getDoubleTy(*context), Doubles, false);

//genero questa funzione con tipo FT e con nome Name, e questa funzione viene messa nel nodo. Create salva anche il numero di parametri
Function *F = Function::Create(FT, Function::ExternalLinkage, Name, *module);

//ExternalLinkage --> la funzione è visibile anche all'esterno del modulo


//Una volta definita la funzione, ora devo semplicemente:

//per ogni argomento della funzione:
unsigned Idx = 0;

for (auto &Arg : F->args())
// ad ogni argomento della funzione diamo il nome che ha specificato il programmatore
	Arg.setName(Args[Idx++]);

//nel parser hai : se "def" proto exp $2.noemit()

//come output avrai : deflare @printval(double) 
//SEMPLICEMENTE SE HAI UN PROTOTIPO, NON GENERO CODICE
//perché non quando definisci la funzione, stai generando anche un prototipo
if (emitcode) {

	F->print(errs());
	
	fprintf(stderr, "\n");

};

return F;

}
```

NON GENERO CODICE quando ho un *PROTOTIPO* perché tanto lo genero quando lo definisco ecco perché c'è il **noemit**. Sennò da anche errore.

Nel file ``morecomplex.k`
Esempio : `def f(x y) x*x-2*x-y+3*y*y` 
Uso una funzione di aiuto `helper()` , guardi semplicemente l'ordine di chiamata delle funzioni.



#### Definizione delle funzioni
una funzion è un **prot** + **body**. Infatti nel costruttore che assegnamo un puntatore al body. Il body deve essere già stato costruito poiché parliamo di parsing bottom-up. 

Il nome della funzione lo prendiamo dal proto, prototipo.
Logica generica è
1. prendo la funzione dal modulo, in realtà sarebbe il prototipo
2. se la funzione non è stata definita, ne creo una
	1. ma se la funziona è stata già definita, allora non la devo ridefinire, semplicemente ritorno nullptr.

touch prova.k
vim prova.k
	def f(x) x+1;
	def f(x,y) x+y;

```c++
FunctionAST::FunctionAST(PrototypeAST* Proto, ExprAST* Body): Proto(Proto), Body(Body) {};

  

Function *FunctionAST::codegen(driver& drv) {

//salvo il prototipo della funzione
Function *function = module->getFunction(std::get<std::string>(Proto->getLexVal())); //prendi il nome della funzione come stringa da lexval, che è un tipo variant. 

// Se la funzione non è già presente, si prova a definirla, innanzitutto

// generando (ma non emettendo) il codice del prototipo

if (!function)
	//se è nullptr, definiamo il prototipo della funziona, generiamo il suo codice
	function = Proto->codegen(drv);
else //se la funzione già esiste nel modulo, semplicemento non la creo, devo ritornare nullptr
	return nullptr;

// Se, per qualche ragione, la definizione "fallisce" si restituisce nullptr

if (!function) 
	//se per qualche motivo codegen ha avuto errore, restituisco nullptr
	return nullptr;

/**Body della funzione***/
//Devo definire un basic block
//ci passo il contesto, il nome del basic block, e la funzione 
BasicBlock *BB = BasicBlock::Create(*context, "entry", function);

//poi dico al builder che il punto d'inserimento da cui cominciare a scrivere nel Basic Block BB
builder->SetInsertPoint(BB);


//per tutti gli argomenti della funzione
for (auto &Arg : function->args()) {

	//creo un blocco che genera un'istruzione di allocazione che alloca 8 byte, mette il puntatore a questi ad un registro SSA ilo cui nome è getName --> infatti lo chiama %x1 e dentro ci mette il puntatore all'indirizzo di memoria allocato. 
	//gurada il risultato di ./komp prova
	AllocaInst *Alloca = CreateEntryBlockAlloca(function, Arg.getName());
	//fai una store, memorizza un double che sta dentro %x nella cella puntata da %x1.
	//semplicemente fai x1 = x, perché i registri non sono riscrivibile e x è il parametro che è un registro irriscrivibile
	builder->CreateStore(&Arg, Alloca);
	
	//prendo il body della funzione, faccio una chiamata che punta all'AST del body
	drv.NamedValues[std::string(Arg.getName())] = Alloca;
	//semepio x+y*z
	//+x*y z --> AST
	//vedo cos'è x, è una variabile, faccio una load, prendo il suo valore
}



if (Value *RetVal = Body->codegen(drv)) {
//guarda cosa fa l'albero e l'output ./komp
	builder->CreateRet(RetVal);
	
	// Effettua la validazione del codice e un controllo di consistenza
	verifyFunction(*function);
	// Emissione del codice su su stderr)
	
	function->print(errs());
	
	fprintf(stderr, "\n");
	
	return function;

}

  

// Errore nella definizione. La funzione viene rimossa

function->eraseFromParent();

return nullptr;

};
```


```sh
$ vim examples/morecomplex.k
```
```.k
extern x(); //ritorna un valore per x
extern y(); //ritorna un valore per y
extern printval(z);
def f(x y) x*x-2*x*y+3*y*y;
def helper() f(x(),y());
def main() printval(helper());

```

uso helper che chiama f passandoci i valori delle funzioni x() e y() per i suoi parametri x e y.

```sh
$ vim rw.cpp
```

per definire un linkage globale che si veda ovunque:
```cpp
#include <iostream>

extern "C" {
    double x();
}
extern "C" {
    double y();
}
extern "C" {
    double printval(double);
}

double x() {
    double tmp;
    std::cout << "Inserisci il valore di x: ";
    std::cin >> tmp;
    return tmp;
}

double y() {
    double tmp;
    std::cout << "Inserisci il valore di y: ";
    std::cin >> tmp;
    return tmp;
}

double printval(double x) {
    std::cout << "Il valore calcolato è " << x << std::endl;
    return 0;
}

```

```sh
clang -c re.cpp
	output è un file rw.o
```

clang++ -o morecomplex.o rw.o
	linking fatto


Supponiamo ora di voler introdurre l'expression IF

Vogliamo poter scrivere coose di questo tipo:
`x>0 ?  1 : 2`
`x=y+1 ? 2*x : 3*y`


1. make clean
2. cp -r slideset12 kaleidoscope-expr-if
3. cd kaleidoscope-expr-of
4. gedit parser.yy

modifichiamo il parser per definirei token per il <,=,?, :

QMARK "?"


5. gedit scanner.ll
	1. ci metto i token in riga 42
6. vim expif.l
	1. 1+(x>1 ? : 2);

aggiungo anche i relazionali per la priorità nel parser sopra al +,-,*,/*:
%left "<" "=";

modifico anche cos'è un'espressione aggiungendo che una exp, può essere anche una expr if. 
exp :
|
|
| exprif     `{$$ = $1}$`

exp if deve anche creare una classe, quindi devi creare la classe per il nodo dell'altbero, ma sempre nel parser

`%type <ExprASRT> * expif*`

devo introdurre una nuova categoria sintattica, un nuovo NON TERMINALE **condexp** 
expif:
	`condexp "?" exp ":" exp {$$ = new IfExprAST($1,$2,$3, $5)};`
```

`condexp:`
	exp "<" exp = {new BinaryAST('<', $1, $3)};
	|exp "=" exp = {new BinaryAST('<', $1, $3)};

TODO
1. introduci la classe IfExprAST che avrà 3 figli ma anche l'operatore

2. devo introdurre una classe  conditional expression
	condexp
```

Dobbiamo modificare anche lo scanner che ritorni LT, EQ se trova <,<=

se provo a fare `bison parser.yy` abbiamo un conflitto shift reduce. 

Se aggiungi l'opzione **-Wconterexamples** vedi il controesempio per l'errore shift reduce. Il problema sta nella priorità, dobbiamo dirgli cosa farne col ":".
- gli dico che i ":" dopo avranno tutta un'espressione


Ora posso compilare anche con flex++ :
`flex++ scanner.ll`

- *Ora dobbiamo andare sul driver in `driver.hpp`*
		- inseriamo la classe IfExprAST :
			
```c++
class IfExprAST: public ExprAST{

private:

	ExprAST* cond; //condizione
	
	ExprAST* trueexp; //qando la condizione è vera
	
	ExprAST* falseexp;
	
	  

public:

	ExprAST(ExprAST* cond, ExprAST* trueexpr, ExprAST* falseexpr);
	
	Value* codegen(driver& drv) override;

}
```


modifico anche il file cpp:
Dobbiamo:
- scrivere il scrivere il codice che valuta il condizionale
	- inserire altri 3 blocchi, true, false e continuazione. 
	- Dobbiamo poi dobbiamo inserire un condizionale che ti salta al blocco vero o false.
	- Alla fine del blocco true, devo poter bypassare il blocco false e andare subito al blocco merge
		- idem per il blocco false. Devo mettere un'istruzione

```c++
IfExprAST(ExprAST* cond, ExprAST* trueexpr, ExprAST* falseexpr):

cond(cond), trueexpr(trueexpr), falseexp(falseexp){};

  
//CI SONO ERRORI GRAMMATICI, ERO DI FRETTA,NON COPIARE IL CODICE
Value* IfExprAST::codegen(driver &drv){

//valutiamo la condizione, che lascia il risultato in un registro ssa

//sul primo figlio che è cond,

Value* CondV = cond->codegen(drv);

if(!CondV) return nullptr; //se non ho avuto un risultato, ritorno nullprt

  
  

//adesso bisogna generare l'istruzione di branch condizionato

//vanno generati i blocchi di tipo basic block per le istruzioni true e false

  

//prima però dobbiamo definire una funzione

//dice in quale funzione sei , getParent

Function* fun = builder->GetInsertBlock()->getParent();

BasicBlock *TrueBB = BasicBlock::Create(*context, "trueblock", fun);

  

//questo basic block true lo devi inserire nel blocco false

//ma non posso metterci "fun" direttamente. Se avessi in "if" annidato, avrei error

//semplicemente creo il blocco.

BasicBlock *FalseBB = BasicBlock::Creat(*context, "falseblock");

  

//faccio la stessa cosa per il merge, lo creo e basta

BasicBlock *MergeBB = BasicBlock::Creat(*context, "mergeblock");

  

//crea un branch condizionale, il risultato lo prendi da CondV, se vero vai in TrueBB, se false vai in FalseBB

builder->CreateCondBr(CondV, TrueBB, FalseBB);

  

//Ora posso generare la parte true, ma devo dire al builder di cambiare blocco

//dobbiamo andare nel blocco TrueBB,

builder->SetInseryPoint(TrueBB);

  

//adesso posso semplicemente richiamare in modo ricorsivo per vedere se ci sono if annidati

Value * TrueV = trueexp->codegen(drv);//che lascerà il suo risultato in un registro SSA

if(!TrueV) return nullptr;

  

//ADESSO POSSO METTERE IL BRANCH AL MERGE

//nel mergeblock, ci sarà l'istruzione phi, che è un'istruzione che ha un numero

//arbitrario di parametri

//phi dice:

//se arrivi da true, il valore sarà un numero,

//se arrivi da false sarà un'altro

//se nel blocco true ho un'altro condizionale, allora l'istruzione di salto arriverà dall'ultimo blocco

//if(true)

//if (false)

//il risultato arriva dall'ultimo blocco.

//Quindi se il blocco true contiene un condizionale, posso avere un'altro insertblock

//IMPORTANTISSIMO, sennò qua vai in segmentationfault

//metto l'istruzione del salto condizionato

builder->CreateBr(MergeBB); //crea una merge al MergeBB, ho finito true

  

//A questo punto possiamo considerare il blocco False, i blocci si inseriscono dalla funzione

//devi inserire il blocco FalseBB alla fine della funzione

//quella che inserisce il blocco è la function non il builder

fun->insertBlock(fun->end(), FalseBB);

  

//l'attuale insert viene impostato a FalseBB

builder-> SetInsertPoint(FalseBB);

//controllo se ha altri blocci

Value* FalseV = falseexp->codegen(drv);

if(!FalseV) return nullptr;

  

//riaggiorno il blocco di salto

FalseBB = builder->GetInsertBlock();

builder->CreateBr(MergeBB);

  

//adesso dico che il builder deve cominciare a inserire nel merge

fun.insert(fun->end(), MergeBB);

builder->SetInsertPoint(MergeBB);

//devo riaggiornare i FLUSSI

//acceta come parametri

// il tipo--> Type::

//si crea in 1+n passi, in questo caso 2 flussi, if ed else

//Creo un'istruzione PHI che aggiunge il valore al registro se arrivi da true o false

PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context),2)

//Resituisci vero come risultato se arrivi da TrueBlock

//mancano i nomi delle funzioni

P->addIncoming(TrueV, TrueBB);

P->addIncoming(FalseV, FalseBB);

  

};```


Per eseguire e controllare

```shell
make all;

cat fact.k
#controlla il fattoriale
./kcomp fact.k
```
###### Analizziamo l'output dei comandi sopra

viene definita fact con un parametro n
1. viene allocata memoria per il parametro n
		1. restituisce il puntatore al registro n1
2. faccio la store del parametro in memoria
3. il parser ha detto che sto facendo un ifexpr
4. controlla n<1
5. fa la load ad n dentro un registro n2.
6. poi viene chiamato ricorsciamente e trova number=1 
7. confromta con **lt** di n2 con 1, $n2 \le 1$
8. br i1, il risultato è un booleano e gli dice di saltare alla label trueBlock o FalseBlock
9. Abbiamo ricorsicvamente generato il codice per il **true**
10. Ora crea ricorsicamente il codice per **false**
	1. fa la load dentro a n3
	2. poi dentro n4
	3. fa la sottrazione 1 da n4 e mette il risultato dentro a **subres**
	4. calltmp, chiamata ricorsica alla funzione
	5. mulres, risultato della moltiplicazione tra n3 e il risultato della funzione 
	6. br label %mergeblock , salta a mergeblock 
11. mergeblock, il risultato di **phi** l, cioè l'1 lo metti in trueblock e il risultato della moltiplicazione lo metti in false block


`clang++ -c callfact.cpp`
`clang++ -o fact fact.o callfact.o` //linker
`./fact` e ci metti 5

Ora vediam l'esempio dell'if annidato :**doublecond.k**
	-controlla il segno di un numero, se +,- 

Controllando l'output
- conforonta il risultato con lo 0 e lo passa ad un  blocco true o false
- vediamo che il false block è composto di tanti true block, false blcok e merge block. 

- ecco perché dobbiamo aggiornare ogni volta l'insert point e sapere da dove arriviamo, cosìché sai cosa tornare nel mergeblock, devi restituire il risultato del blocco da dove entri. 


Per implementare il for: 
1. verifico la condizione da partenza e saltare al codice per la condizione di fine
2. il codice per la condizione di fine o va dopo il for o al body
3. Dal body, passo al codice per l'aggiornamento che passa al blocco finale.

Sono 5 blocchi per il for.

`cat rwfact_withmain.k` Un fattoriale ma il main sta dentro a Kaleidoscope, quindi ho oltre alle funzioni, anche la definizione del main program. 

`cat rwfact.cpp` : è sempre uguale.

`./kcomp rwfact_withmain.k 2> rw_withmain.ll`
`cat rw_withmain.ll`

`clang++ -c rw_fact.cpp`
`clang++ -o rwfact rwfact.o rwfact_withmain.o`
`./rwfact`


#### Memoria
Dobbiamo fare un'estensione al nostro linguaggio. Rimane cmq un linguaggio funzionale. 

Alcuni linguaggio infatti abbiamo una cosa del genere `let x=3 in : x=2*x`.
- sia x=3 nell'espressione x=2*x*

```
{
var x=3;
var y=5*x;
f(x y);
} *5

--> questa è un'espressione che moltiplichiamo per 5

La chiameremo BlockExpression che è cmq una expression. La sintassi è {}, dentro le parentesi c'è una sequenza di "var", un'espressione e poi un'espressione f()
```

Esempio concreto
```kaleidoscope
def fibonacci(n)
	n<2 ? 1 : 
		{
		var f2 = fibonacci(n-2);
		var f1 = fibonacci(n-1);
		f1+f2 //valore dell'espressione
		}
```


Cominciamo dal parser
`cp -r KaleidoscopeIfExpr KaleidoscopeBlockExpr`

nel parser.yy

Il valore della BlockExpression è il valore finale, non possiamo riassegnare valori. 

Qua andremo a definire anche la regola di visibilità : **lexical scope** (se ho due variabili chiamate con lo stesso nome, quale scelgo? n=1; {n=2}, prendo n=2)

###### Definiamo i nuovi token 
intanto l'EQ lo mettiamo in ==

ASSIGN "="
LBRACE "{"
RBRACE "}"
VAR "var"


###### Modifichiamo la grammatica
aggiungiamo a exp la blockexpr
exp: 
| 
| blockexp  {`$$ = $1`}

blockexp:
  "{" vardefs ";" exp "}"  {`$$ = new BlockExprAST($2,$4)`}

//vardef può essere o una sola variabile o più variabili
/var a=1
oppure 
//var a=1;
//var b=2;
vardefs:
  vdef
|  vdef ; vardefs  {`$$ = new VarDefs`}