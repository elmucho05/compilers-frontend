%{
#include <stdexcept>
#include "parser.hpp"
void illegal(char c);
int value;
%}

integer         [[:digit:]]+

%option noyywrap

%%
[ \t\n]     { /* Ignoriamo i separatori */ }
{integer}   { value = std::stoi(yytext); return tok_num; }
"*"         { return tok_times; }
"+"         { return tok_plus; }
"("         { return tok_left; }
")"         { return tok_right; }
<<EOF>>     { return tok_eof; }
.           { illegal(yytext[0]); }

%%

void illegal(char c) {
   throw std::invalid_argument( "Trovato un carattere illegale" );
}
