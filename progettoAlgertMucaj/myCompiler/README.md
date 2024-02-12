# Progetto di Linguaggi e Compilatori
by Algert Mucaj

Il programma analizza il codice sorgente scritto secondo le specifiche della grammatica data, genera un AST e, infine, produce codice intermedio ottimizzato per ulteriori fasi di compilazione o esecuzione.

Il compilatore implementa la grammatica di *quarto livello*, quindi genera codice intermedio per tutti i programmi di test forniti.

#### Note implementative
**Gestione delle Variabili**: Una variabile definita all'interno di un blocco ha la precedenza sui parametri di funzione con lo stesso nome, che a loro volta hanno la precedenza sulle variabili globali con lo stesso nome.

**Cicli for**: Supportati attraverso una gestione dettagliata dei blocchi per la condizione di loop, il corpo del ciclo e l'incremento.

**Inizializzazione degli Array**: L'inizializzazione richiede la specifica del numero di elementi e l'assegnazione di valori coerenti con la dichiarazione. Il che significa che una dichiarazione del tipo A[2] ={5,7,8} generra un errore.

### Prerequisiti
Questo progetto è stato implementato su Debian 12 Bookworm e non è stato testati su altri SO.

Per compilare e utilizzare questo progetto, è necessario avere installato LLVM sulla propria macchina. 
Di conseguenza, nel Makefile principale va specificata la versione LLVM che nel mio caso è llvm-16 come mostrato nell'esempio:

```makefile
clang++ -c kcomp.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
```

Un'ulteriore modifica circa la versione di LLVM va fatta anche nello script *tobinary* nella cartella *test_progetto*, principalmente riguardante i comandi `llvm-16` e `llc-16` dove 16 è la mia versione di llvm.
```sh
#!/bin/bash
fn=${1%.*}
llvm-as-16 $1
llc-16 ${fn}.bc
as -o ${fn}.o ${fn}.s
```
