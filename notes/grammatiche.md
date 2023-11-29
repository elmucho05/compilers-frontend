Il compito del *parser* è di stabilire se una sequenza di token rappresenta un programma sintatticamente corretto e, se questo è il caso, di fornire una descrizione della struttura sintattica. 


> Un **linguaggio regolare NON** può includere frasi in cui una porzione di frase condizionata da una precedente porzione di frase. 

```c
// Il seguente codice contiene un errore di sintassi
while (a>0 {a=a-1}
```

Quindi possiamo dire che un linguaggio regolare non può descrivere la precedente porzione di codice, poiché tutte le frasi che hanno *n* parentesi aperte, *devono* avere *n* parentesi chiuse. 



### Cos'è una grammatica
---
Una **grammatica** è un formalismo per definire linguaggi.

La modalità con cui una grammatica definisce un linguaggio è di natura "generativa", cioè esiste un modo con cui usando la grammatica, è possibile *generare/derivare* tutte le frasi del linguaggio-


Una grammatica G, formalmente è definita come una **quadrupla** di elementi : $G = (N, T, P, S)$

dove : 
- $N$ : è un insieme di simboli detti "NON-TERMINALI"
- T : è un insieme di simboli detti "TERMINALI"
- P : è l'insieme delle produzione che hanno la forma X-> Y dove X e Y possono essere terminali e non terminali
- $S \in N$ è il simbolo iniziale detto **assioma**

Una grammatica *regolare* è detta **lineare**
```
Esempio di Grammatica :
Questa è una grammatica lineare a sinistra
A --> xB oppure A -->x
x è un TERMINALE
B è un non terminale


Questa invece è un grammatica lineare a destra

A --> Bx oppure A --> x
x è un TERMINALE
B è un non terminale



```


### Grammatiche Context-Free
---
Per la definizione della sintassi dei linguaggi di programmazione, abbiamo bisogno di un particolare tipo di linguaggio chiamato **libero dal contesto/context-free**. 

**Produzioni:** regole di riscrittura
I linguaggi liberi sono generabili da grammatiche in le produzioni hanno la seguente forma: $A->\alpha$

dove A è un NON-Terminale, e $\alpha$ è una qualsiasi stringa di terminali o non terminali. 

***Esistono anche grammatiche ricorsive*** ed hanno la seguente forma: $\alpha -> \beta$

##### Derivazioni e produzioni
**Produzioni:** regole di riscrittura 
	- Ad esempio, una produzione del tipo $A -> aA$ si può leggere come: *"il simbolo A può essere sostituito(**riscritto**) dal simbolo terminale **a**  oppure ancora dal simbolo non terminale **A**"*


>Una ***derivazione*** quindi può essere definita come il processo mediante il quale, a partire dall'assioma ed applicando una sequenza di produzioni, si ottiene la stringa formata da *soli terminali*. 

Una derivazione è composta da più applicazioni di produzioni e dunque da più *sequenze intermedie* : $S => \alpha_1 => ... => \alpha_i => \alpha_k$ dove $\alpha$ è una stringa. 

Una grammatica descrive(genera) il linguaggio formato dalle sequenze di simboli terminali derivabili a partire dall'assioma *S*. 


Consideriamo la grammatica Gn,m = (N , T , P, S) così definita:
N = {S, A, B};
T = {a, b};
S = S;
P contiene le seguenti produzioni:
```
S -> eps, S -> A
A -> a, A -> aA, A-> B
B -> bB, B-> b

Nel linguaggio che genera questa grammatica, è inclusa la stringa *ab* perché 
S => A => aA => aB => ab
```

Spiegazione della grammatica: 
- `aA => aB` significa che dalla stringa **aA** si passa alla stringa successiva
	- questo è possibile grazie al fatto che nella grammatica, A può diventare B , `A -> B`

> La stringa di *terminali* generata da una derivazione è detta ***frase del linguaggio****

> Le stringhe che in precedenza abbiamo indicato come "passaggi intermedi" sono chiamate ***forme di frase*** . Si noti che una forma di frase deve includere almeno un simbolo non terminale che deve ancora essere riscritto. 

Una grammatica può essere espressa elencando solo le produzioni. La grammatica precedente può essere riscritta: 


```
S -> ϵ
S -> S -> A
A -> a
A -> aA
A -> B
B -> bB
B -> b
```

Da notare che i simboli **TERMINALI** **compaiono** solo a **destra** delle produzione mai a sinistra. 


> Di solito se X -> Y e X -> Z, scriviamo semplicemente `X-> Y | Z`

Usando questa convenzione, la nostra grammatica diventa: 
```
S -> ϵ | A
A -> a | A | aA | B
B -> bB | b
```

