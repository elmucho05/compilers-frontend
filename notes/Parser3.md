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
