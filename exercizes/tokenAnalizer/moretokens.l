%{
#include <iostream>
using namespace std;
%}

DIGIT   [0-9]
DIGIT1  [1-9]
LETTER  [A-Za-z]
SEP     [ \t\n]

/* read only one input file */
%option noyywrap

%%
"+"                    		{ cout << "        operatore <" << yytext[0] << ">" << endl; }
"-"                     	{ cout << "        operatore <" << yytext[0] << ">" << endl; }
"*"                     	{ cout << "        operatore <" << yytext[0] << ">" << endl; }
"/"                     	{ cout << "        operatore <" << yytext[0] << ">" << endl; }
"("                     	{ cout << "          openpar <" << yytext[0] << ">" << endl; }
")"                     	{ cout << "        closedpar <" << yytext[0] << ">" << endl; }
"="                  		{ cout << "        operatore <" << yytext[0] << ">" << endl; }
"for"                           { cout << "          keyword <" << yytext    << ">" << endl; }
{DIGIT1}{DIGIT}*        	{ cout << "           numero <" << yytext    << ">" << endl; }
{LETTER}({LETTER}|{DIGIT})*	{ cout << "   identificatore <" << yytext    << ">" << endl; }
{SEP}*                          {}
.                       	{ cout << "Token sconosciuto <" << yytext[0] << ">" << endl; }
%%
int main(int argc, char** argv) {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
    return 0;
}
