Il compito del *parser* è di stabilire se una sequenza di toke rappresenta un programma sintatticamente corretto e, se questo è il caso, di fornire una descrizione della struttura sintattica. 


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

