Classi Aggiunte: 
- GlobalVarAST: classe per definire le variabili globali
- AssignmentAST: classe per gli assegnamenti 
- IfSTMT: classe per l'if then/else
- ForSTMT: classe per il costrutto FOR
- InitFor: classe per l'init del for che può essere un varBinding o un Assignment. Quindi il problema risulta quando ci sarà da fare la codegen che può essere un Value* o un AllocaInst e, quindi, bisognerà gestire i due casi diversamente. Il tutto è risolto con una variant, la classe InitFor conterrà un attributo che potrà essere un VarBinding o un Assignment
- StmtAST: classe "fantasma" che avrà come figli Expr, Block, Assignment, If e For

Modifiche a classi già esistenti: 
- VarBindingAST: è possibile ora definire una variabile senza valore (es. var x; invece che var x=2;)
- BlockAST: si aggiunge un vettore di VarBinding per le varie definizioni a inizio blocco seguito da un vettore di Stmt, l'ultimo Stmt conterrà il valore di ritorno del blocco. 
- VarBindingAST & VariableExprAST: ora, se la variabile non è definita nella Symbol Table, si controlla che non sia definita anche globalmente prima di lanciare errore. 

Modifiche allo scanner:
-aggiunti i return dei vari Token. 

