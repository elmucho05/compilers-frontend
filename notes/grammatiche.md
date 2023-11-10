Il compito del *parser* è di stabilire se una sequenza di toke rappresenta un programma sintatticamente corretto e, se questo è il caso, di fornire una descrizione della struttura sintattica. 


> Un **linguaggio regolare NON** può includere frasi in cui una porzione di frase condizionata da una precedente porzione di frase. 

```c
// Il seguente codice contiene un errore di sintassi
while (a>0 {a=a-1}
```

Quindi possiamo dire che un linguaggio regolare non può descrivere la precedente porzione di codice, poiché tutte le frasi che hanno *n* parentesi aperte, *devono* avere *n* parentesi chiuse. 




