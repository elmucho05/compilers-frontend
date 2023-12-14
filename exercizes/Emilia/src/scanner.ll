%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <cmath>
# include "driver.hpp"
# include "parser.hpp"

# undef yywrap
# define yywrap() 1

#if defined __GNUC__ && 7 <= __GNUC__
# pragma GCC diagnostic ignored "-Wnull-dereference"
#endif

yy::parser::symbol_type check_keywords(std::string lexeme, yy::location& loc);
%}

%option noyywrap nounput batch debug noinput

id      [a-zA-Z][a-zA-Z_0-9]*
fpnum   [0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
fixnum  (0|[1-9][0-9]*)\.?[0-9]*
num     {fpnum}|{fixnum}
blank   [ \t\r]
comment \/\/.*

%{
  # define YY_USER_ACTION loc.columns(yyleng);
%}
%%
%{
  yy::location& loc = drv.location;
  loc.step ();
%}
{blank}+   loc.step ();
{comment}  loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();

"-"      return yy::parser::make_MINUS     (loc);
"+"      return yy::parser::make_PLUS      (loc);
"*"      return yy::parser::make_STAR      (loc);
"/"      return yy::parser::make_SLASH     (loc);
"%"      return yy::parser::make_MODULO    (loc);
"^"      return yy::parser::make_CARET     (loc);
"("      return yy::parser::make_LPAREN    (loc);
")"      return yy::parser::make_RPAREN    (loc);
";"      return yy::parser::make_SEMICOLON (loc);
","      return yy::parser::make_COMMA     (loc);
":"      return yy::parser::make_CONCAT    (loc);
"!"      return yy::parser::make_NOT       (loc);
">"      return yy::parser::make_GT        (loc);
"<"      return yy::parser::make_LT        (loc);
"<="     return yy::parser::make_LE        (loc);
">="     return yy::parser::make_GE        (loc);
"=="     return yy::parser::make_EQ        (loc);
"!="     return yy::parser::make_NE        (loc);
"="      return yy::parser::make_ASSIGN    (loc);
"["      return yy::parser::make_LSQUARE   (loc);
"]"      return yy::parser::make_RSQUARE   (loc);

{num}      {
  errno = 0;
  double n = strtod(yytext, NULL);
  if (! (n!=HUGE_VAL && n!=-HUGE_VAL && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "Float value is out of range: "
                                    + std::string(yytext));
  return yy::parser::make_NUMBER (n, loc);
}
{id}       return check_keywords(yytext, loc);
.          {
             throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));
}
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type check_keywords(std::string lexeme, yy::location& loc)  {
   if (lexeme == "fun") 
     return yy::parser::make_FUN(loc);
   else if (lexeme == "extern")
     return yy::parser::make_EXTERN(loc);
   else if (lexeme == "if")
     return yy::parser::make_IF(loc);
   else if (lexeme == "then")
     return yy::parser::make_THEN(loc);
   else if (lexeme == "else") 
     return yy::parser::make_ELSE(loc);
   else if (lexeme == "for")
     return yy::parser::make_FOR(loc);
   else if (lexeme == "do")
     return yy::parser::make_DO(loc);
   else if (lexeme == "end")
     return yy::parser::make_ENDKW(loc);
   else if (lexeme == "with")
     return yy::parser::make_WITH(loc);
   else if (lexeme == "while")
     return yy::parser::make_WHILE(loc);
   else if (lexeme == "arrof")
     return yy::parser::make_ARROF(loc);
   else
     return yy::parser::make_IDENTIFIER (yytext, loc);
}

void driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void driver::scan_end ()
{
  fclose (yyin);
}
