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
	- `void scan_end scan_begin()` 
	- `yy::location location;` usata dallo scanner per localizzare i token
	- `void codegen()` funzione generatrice del codice, ogni classe avrà la sua relativa, la classe delle espressioni, genera codice per le espressioni. 
	- std::variant <> lexval , l'abbiamo visto in classe.


#### Driver.cpp 
Implementazione della classe driver.

Ci servono oggetti di 3 classi particolari:
1. **LLVMContext** : classe opaca che contiene tutte le strutture dati importanti per generare codice
2. **Module**
3. **IRBuilder** : metodi che generano internamente rappresentazioni di tutte le istruzioni, poi ad un certo punto le possiamo emettere. Costruiscono quindi quindi le varie istruzioni del codice intermedio. 

impelmentazioni delle funzioni 

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

Si scende a sx, genera il codice, il risultato calcolato viene rappresentato da un registro : `Value *f ` è un registro *SSA* 

###### Ora guardiamo la **Binary expression Tree**
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

// Non viene generata un'struzione; soltanto una costante LLVM IR

// corrispondente al valore float memorizzato nel nodo

// La costante verrà utilizzata in altra parte del processo di generazione

// Si noti che l'uso del contesto garantisce l'unicità della costanti


/*
non posso scrivere direttamente return val, anche perché codegen riece a vedere l'attributo. 

- perché le costanti devono essere uniche e sono mantenute tutte da questo contesto. Nel contest sono rappresentate nel Conetext in modo unico. 
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


std::vector<Value *> ArgsV;

for (auto arg : Args) {

	ArgsV.push_back(arg->codegen(drv));
	
	if (!ArgsV.back())
	
	return nullptr;
	
	}

return builder->CreateCall(CalleeF, ArgsV, "calltmp");

}
```