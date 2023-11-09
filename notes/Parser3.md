Un parser bottom-up procede per riduzione. I parser di tipo **shift reduce** sono quelli più diffusi perché sono le due operazioni che i parser fanno più spesso. 
Per costruire un parser shift reduce, serve 

Lo *shift* è uno spostamento di un caretteri sullo stack.

Il *reduce* sostituisce sullo stack gli ultimi simboli inseriti con i simbolo A. 

La seguente grammatica è utile per il parser bottom up
```grammar
E → E+T | T
T→ T ×F | F
F→ n | (E)
```

![[Pasted image 20231109162554.png]]

L'attuale tabella illustra il contenuto dello stack e l'input ancora da leggere se venisse applicato l'approccio "greedy". 


### Struttura di un parser LR
Un parser è caratterizzato da un programma di controllo che ha accesso ad uno stack e ad una tabella di parsing. 

![[Pasted image 20231109163925.png]]

- Le tabelle prescrivono il comportamento del programma di controllo in funzione del contenuto dello stack e dei primi k caratteri presenti in input (per noi k = 1).
- Lo stack, contiene stati anziché simboli.
- Ma ogni stato è associato univocamente ad un simbolo della grammatica.

##### Caso generico e Algoritmo di funzionamento
Come nel caso generico di parser shift-reduce, possiamo quindi ricostruire la forma di frase corrente, usando i simboli memorizzati sullo stack concatenati con i simboli ancora sullo stream di input. 

Il funzionamento del parser è definito come segue.
1. Inizialmente, lo stack contiene un solo stato (lo stato iniziale,naturalmente).
2. Al generico passo, sia q lo stato in cima allo stack e x il prossimo carattere in input.
3. Se ACT ION [q, x] = shift r, il parser avanza il puntatore di input e inserisce lo stato r sullo stack.
4. Se ACT ION [q, x] = reduce i, il parser utilizza la i-esima produzione (secondo una numerazione arbitraria ma prefissata). Più precisamente,se A → α è tale produzione, il parser rimuove ki = |α| stati dallo stack e vi inserisce lo stato GOT O [q′ , A] dove q′ è lo stato sulla cima dello stack dopo le ki rimozioni.
5. Il parser si arresta in seguito ad accettazione o errore.


Esempio da STUDIARE
```productions
S -> (S)S
S -> eps
```

E la seguente tabella di parsing :
![[Pasted image 20231109164609.png]]
![[Pasted image 20231109164629.png]]

La parte più difficile è riuscire a creare la *Tabella di parsing*.
- ogni volta che faccio le reduce, facciamo paritre del codice

Prima costruiamo l'albero e poi facciamo una visita dell'albero per costruire il codice intermedio da generare. 

#### Cosa sono questi stati?
Sono stati di un automa particolare. Parliamo di uno automa con una grammatica particolare. 

Qual è il significato di un item associato ad una data produzione?
Un item è una produzione con inserito un marcatore che sarà il punto(.).

Il "punto" sta ad indicare il punto al cui il processo di parsing è arrivato. 
Se mettiamo il "*puntino*" significa che siamo arrivati al momento in cui il parser deve riconoscere la parte destra di una produzione. 

Ad esempio, gli item associati alla produzione S → (S)S sono:
S → ·(S)S , S → (·S)S , S → (S·)S , S → (S) · S e S → (S)S·.
Ad una produzione tipo S → eps è associato il solo item S → ·.
S → ·(S)S  -> arrivati a questo punto, dobbiamo conoscere un'intera sequenza bilanciata. 



Intuitivamente, esso indica la posizione alla quale siamo arrivati nel
processo di riconoscimento della parte destra della produzione stessa.
Ad esempio, l’item S → (S) · S indica che abbiamo riconosciuto una
stringa descritta da (S) e che ci “attendiamo” di riconoscere una
stringa descrivibile da S .
Un item con il puntino in fondo indica quindi che il processo di
riconoscimento della parte destra è completato e dunque che si può
operare la riduzione (vedremo sotto quale altra condizione).

![[Pasted image 20231109165853.png]]

Il puntino quindi significa che stiamo all'inizio. Quando si sposta, dice che abbiamo riconosciuto l'elemento grammaticale.Quando sta alla fine, significa che siamo arrivati alla fine. 

