# Emilia
### Requisiti
Il linguaggio **Emilia** supporta:
-  Il costrutto ***if-else***
    ```
    if (input > 10) then
        echo (1)
    else
        echo (0)
    end
    ```
    Dimostrazione nel file `input/1.if-else.em`
- Il costrutto ***while***
    ```
    while contatore > 0 do
        contatore = contatore - 1:
        echo(contatore)    
    end
    ```
    Dimostrazione nel file `input/5.while.em`
- L'***operatore unario -***, e le ***espressioni composte*** 
    ```
    echo (-variabile + 18*variabile - variabile + 2)
    ```
    Dimostrazione nel file `input/2.espressione.em`
- Il costrutto ***for***
    ```
    for i = 0, i < input, 1 do 
        echo(i)
    end 
    ```
    Dimostrazione nel file `input/6.for.em`
- L'assegnamento delle variabili per blocchi tramite il ***with***
    ```
    with a=input do
        input = input-1:
        echo(input):
        echo(a)
    end
    ```
    Dimostrazione nel file `input/7.with.em`
### Linguaggio di programmazione
---

### Scelte di sviluppo
- File sorgenti .em
    - Per poter dire: "in cosa stai programmando? Io in un linguaggio in cui i file sono punto ehm"
- Funzione echo e non print
    - Torna a gran voce echo per poter risollevare la discussione se si pronuncia come la parola italiana **eco** o come la parola **vecchio** in dialetto senza la v "ecio"
- Fun e non def, void, function, ...
    - Parola chiave per dichiarare una funzione. Se integer diventa int, allora anche function diventa fun (e per la traduzione inglese)

# files
- `src/scanner.ll` Vengono definite macro per semplificare le espressioni regolari
    - Contiene il codice sorgente per l'analizzaore lessicale (che divide l'input in tokn)
    - Usa espressioni regolari per riconoscere i token
    - creazione del file `src/scanner.cpp` usando il seguente comando:
    ```sh
    flex -o src/scanner.cpp src/scanner.ll
    ```
