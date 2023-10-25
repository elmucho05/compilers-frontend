/***************************************************************
****** Parser a discesa ricorsiva con backtracking per   *******
****** la grammatica senza cicli presentata nella slide  *******
****** 27 del set "Analisi sintattica (PARTE PRIMA)      *******
***************************************************************/
#include <iostream>
#include <FlexLexer.h>
#include <string>
#include <vector>
#include <map>
#include "parser.hpp"
using namespace std;

extern int value;
bool E(int& i); // una procedura per il non terminale E e Ep
bool Ep(int& i); // i, è il puntatore di input, serve passarlo


// codifico i terminali come numero
const int nonterm_E = 1;
const int nonterm_Ep = 2;
const int eps = 0;

class Token {
public:
    Token(TokenType t): t(t) {};
    Token(TokenType t, int v): t(t), v(v) {};
    TokenType t;
    int v;
};

vector<Token*> iseq; // Vettore che contiene la sequenza di token da analizzare

/* Rappresentazione delle produzioni:
   1) La parte destra di una produzione è rappresentata come lista
      di numeri interi
   2) Le produzioni di uno stesso simbolo di testa (qui solo E e E') sono
      poi inserite in uno stesso "vettore di vettori di interi"
*/
      
std::vector<int> prod1{tok_left, nonterm_E, tok_right, nonterm_Ep};  // E --> (E)E'
std::vector<int> prod2{tok_num, nonterm_Ep};                         // E --> nE'
std::vector<int> prod3{tok_plus, nonterm_E, nonterm_Ep};             // E'--> +EE'
std::vector<int> prod4{tok_times, nonterm_E, nonterm_Ep};            // E'--> *EE'
std::vector<int> prod5{eps};                                         // E'--> eps
// 
std::vector<vector<int>> Eprods{prod1,prod2};
std::vector<vector<int>> Epprods{prod3,prod4,prod5};
// array di stringhe che rappresentano le produzioni in modo "human readable"
string Edisplay[2] = {"E --> (E)E'","E --> nE'"};
string Epdisplay[3] = {"E'--> +EE'","E'--> *EE'","E'--> eps"};
/************************************/

bool isterm(int v) {   // Test per simbolo non terminale
    return v<=0;
}

bool iseps(int v) {    // Test per epsilon
    return v==0;
}

/* Funzione "driver" per le singole funzioni corrispondenti ai non terminali 
   Lo scopo è rendere più leggibile il codice spostando il test del non terminale
   su cui da E e Ep al driver
*/
bool evalN(int nonterm_N, int& i) {
    if (nonterm_N == nonterm_E) {
        return E(i);
    } else {
        return Ep(i);
    }
}

// Funzioni corrispondenti ai non terminali
bool E(int& i) {
    // Le due produzioni con testa E vengono provate in
    // quest'ordine: prima E->(E)E' e poi E->number E'
    int saveptr = i;    // Salvataggio del puntatore per eventuale backtracking
    int n = Eprods.size();  // n = numero di produzioni con E in testa (2) 
    for (int j=0; j<n; j++) {  // Le proviamo tutte prima di dichiarare (event.) fallimento
        bool fail = false;
        for(int v=0; v<Eprods[j].size(); v++) { // Scansione della parte dx della pruduzione i
            int t = Eprods[j][v];
            if (isterm(t) and iseq.at(i)->t==t) {// Caso t terminale e match con input 
	      i++;
              continue;
            } else if (not isterm(t) && evalN(t,i)) { // Caso ricorsivo termina con successo
                continue;
            }
            i = saveptr; // restore the input pointer  // Insuccesso, ripristiniamo puntatore
            fail = true;
            break;
        }
        if (not fail) {   // Una produzione è stata analizzata con successo, procediamo
	  std::cout << Edisplay[j] << endl;
	  return true;
	}
    }
    return false;  // Tutte le produzione hanno fallito, restituiamo false al chiamante
} 

bool Ep(int& i) {
    // Le due produzioni con testa E' vengono provate in
    // quest'ordine: E'->+EE', E'->*EE', E'->eps
    // Non ci sono commenti perché la logica è esattamente 
    // la stessa della funzione per E
    int saveptr = i;
    int n = Epprods.size();
    for (int j=0; j<n; j++) {
        bool fail = false;
        for(int v=0; v<Epprods[j].size(); v++) {
            int t = Epprods[j][v];
            if (iseps(t)) {
                continue;
            }
            if (isterm(t) and iseq.at(i)->t==t) {
	      i++;
	      continue;
            }
	    if (not isterm(t) && evalN(t,i)) {
                continue;
            }
            i = saveptr; // restore the input pointer
            fail = true;
            break;
}
        if (not fail) {
	  std::cout << Epdisplay[j] << endl;
	  return true;
	}
    }
    return false;
}

int main()
/* Per semplicità la stringa di input viene letta interamente e "tokenizzata".
   Solo dopo inizia il parsing. Questo viene fatto perché "questo" parser funziona con
   backtracking e naturalmente la sua implementazione è più agevole se la sequenza
   è in memoria e su file
*/
{
  FlexLexer* lexer = new yyFlexLexer;
  Token* t;
  int tok;
  std::cout << "Starting...\n";;
  while ((tok = lexer->yylex()) && (tok != tok_eof)) { // Finché lo scanner passa token ...
      if (tok == tok_num) {                            // ... se il token è un numero c'è
          t = new Token(tok_num,value);                // anche il valore, 
      } else {
	t = new Token(static_cast<TokenType>(tok));    // altrimenti c'è solo il nome/tipo
      }
      iseq.push_back(t);                               // Inseriamo in fondo alla sequenza
  }
  iseq.push_back(new Token(tok_eof));
  // Lettura terminata, inizia il parsing
  int i = 0;  // Puntatore di input (punta al token corrente)
  
  if (E(i) and iseq.at(i)->t == tok_eof)// Se la funzione per E (assioma) restituisce true e
      std::cout << "Accept\n";          // il puntatore è su eof, il parsing ha avuto successo
  else  std::cout << "Reject\n";        // Altrimenti la stringa non è stata riconosciuta
  return 0;
}

