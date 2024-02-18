%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.location.file none
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  #include <exception>
  class driver;
  class RootAST;
  class ExprAST;
  class NumberExprAST;
  class VariableExprAST;
  class ArrayExprAST;
  class CallExprAST;
  class FunctionAST;
  class SeqAST;
  class PrototypeAST;
  class GlobalVarAST;
  class GlobalArrayAST;
  class BlockAST;
  class StmtAST;
  class IfStmtAST;
  class ForStmtAST;
  class InitAST;
  class BindingAST;
  class AssignmentAST;
  class VarBindingAST;
  class VarAssignmentAST;
}

//context
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  SEMICOLON  ";"
  COMMA      ","
  MINUS      "-"
  PLUS       "+"
  STAR       "*"
  SLASH      "/"
  LPAREN     "("
  RPAREN     ")"
  QMARK	     "?"
  COLON      ":"
  LT         "<"
  EQ         "=="
  ASSIGN     "="
  LBRACE     "{"
  RBRACE     "}"
  LSQBRACE   "["
  RSQBRACE   "]"
  EXTERN     "extern"
  DEF        "def"
  VAR        "var"
  GLOBAL     "global"
  IF         "if"
  ELSE       "else"
  FOR        "for"
  AND        "and"
  OR         "or"
  NOT        "not"
;
%token <std::string> IDENTIFIER "id"
%token <double> NUMBER "number"

%type <ExprAST*> exp
%type <ExprAST*> idexp
%type <ExprAST*> expif
%type <ExprAST*> condexp
%type <ExprAST*> relexp
%type <ExprAST*> initexp
%type <std::vector<ExprAST*>> optexp
%type <std::vector<ExprAST*>> explist
%type <RootAST*> program
%type <RootAST*> top
%type <std::vector<StmtAST*>> stmts
%type <StmtAST*> stmt
%type <IfStmtAST*> ifstmt
%type <ForStmtAST*> forstmt
%type <FunctionAST*> definition
%type <PrototypeAST*> external
%type <GlobalVarAST*> globalvar
%type <PrototypeAST*> proto
%type <std::vector<std::string>> idseq
%type <BlockAST*> block
%type <std::vector<BindingAST*>> vardefs
%type <InitAST*> init
%type <AssignmentAST*> assignment
%type <BindingAST*> binding

%%
%start startsymb;

startsymb:
    program                 { drv.root = $1; }

program:
    %empty               { $$ = new SeqAST(nullptr,nullptr); }
|   top ";" program      { $$ = new SeqAST($1,$3); };


top:
    %empty                { $$ = nullptr; }
|   definition            { $$ = $1; }
|   external              { $$ = $1; }
|   globalvar             { $$ = $1; };  

definition:
    "def" proto block       { $$ = new FunctionAST($2,$3); $2->noemit(); };

external:
    "extern" proto        { $$ = $2; };

proto:
    "id" "(" idseq ")"    { $$ = new PrototypeAST($1,$3);  };

globalvar:
    "global" "id"                       { $$ = new GlobalVarAST($2); } 
|   "global" "id" "[" "number" "]"      { $$ = new GlobalArrayAST($2,$4); };  


idseq:
    %empty                { std::vector<std::string> args;
                         $$ = args; }
|   "id" idseq            { $2.insert($2.begin(),$1); $$ = $2; };

%left ":" "?";
%right "not";
%left "and" "or";
%left "<" "==";
%left "+" "-";
%left "*" "/";


stmts:
    stmt                   { std::vector<StmtAST*> stmts;
                            stmts.insert(stmts.begin(), $1);
                            $$ = stmts; }
|   stmt ";" stmts        { $3.insert($3.begin(), $1);
                            $$ = $3; }

stmt:
    assignment            { $$ = new StmtAST($1); }
|   block                 { $$ = new StmtAST($1); }
|   ifstmt                { $$ = new StmtAST($1); }
|   forstmt               { $$ = new StmtAST($1); }
|   exp                   { $$ = new StmtAST($1); };

forstmt:
    "for" "(" init ";" condexp ";" assignment ")" stmt  {$$ = new ForStmtAST($3,$5,$7,$9); };

init:
    binding                 { $$ = $1; }
|   assignment              { $$ = $1; };

assignment:
    "-" "-" "id"                    { $$ = new VarAssignmentAST($3, new BinaryExprAST('-',new VariableExprAST($3),new NumberExprAST(1.0)));}
|   "+" "+" "id"                    { $$ = new VarAssignmentAST($3, new BinaryExprAST('+',new VariableExprAST($3),new NumberExprAST(1.0)));}
|   "id" "=" exp                    { $$ = new VarAssignmentAST($1,$3); }
|   "id" "[" exp "]" "=" exp        { $$ = new ArrayAssignmentAST($1,$3,$6); };


block:
    "{" stmts "}"             { std::vector<BindingAST*> tmp; 
                                $$ = new BlockAST(tmp, $2);}
|   "{" vardefs ";" stmts "}" { $$ = new BlockAST($2,$4); }

vardefs:
    binding                 { std::vector<BindingAST*> definitions;
                            definitions.push_back($1);
                            $$ = definitions; }
|   vardefs ";" binding     { $1.push_back($3);
                            $$ = $1; }

binding:
    "var" "id" initexp                                  { $$ = new VarBindingAST($2,$3); }
|   "var" "id" "[" "number" "]"                         { $$ = new ArrayBindingAST($2,$4); }
|   "var" "id" "[" "number" "]" "=" "{" explist "}"   { $$ = new ArrayBindingAST($2,$4,$8); }


exp:
    exp "+" exp           { $$ = new BinaryExprAST('+',$1,$3); }
|   exp "-" exp           { $$ = new BinaryExprAST('-',$1,$3); }
|   exp "*" exp           { $$ = new BinaryExprAST('*',$1,$3); }
|   exp "/" exp           { $$ = new BinaryExprAST('/',$1,$3); }
|   "-" idexp             { $$ = new BinaryExprAST('-',new NumberExprAST(0.0),$2); }  
|   idexp                 { $$ = $1; }
|   "(" exp ")"           { $$ = $2; }
|   "number"              { $$ = new NumberExprAST($1); }
|   "-" "number"          { $$ = new BinaryExprAST('-',new NumberExprAST(0.0),new NumberExprAST($2)); }  
|   expif                 { $$ = $1; };

initexp:
    %empty                { $$ = new NumberExprAST(0.0); }
|   "=" exp               { $$ = $2; };
                      
expif:
    condexp "?" exp ":" exp { $$ = new IfExprAST($1,$3,$5); }

ifstmt :
    "if" "(" condexp ")" stmt               { $$ = new IfStmtAST($3,$5,nullptr); }
|   "if" "(" condexp ")" stmt "else" stmt   { $$ = new IfStmtAST($3,$5,$7); };

condexp :
    relexp                      { $$ = $1; }   
|   relexp "and" condexp        { $$ = new BinaryExprAST('&',$1,$3); }
|   relexp "or" condexp         { $$ = new BinaryExprAST('|',$1,$3); }
|   "not" condexp               { $$ = new UnaryExprAST('!',$2); }
|   "(" condexp ")"             { $$ = $2; };   

relexp:
    exp "<" exp           { $$ = new BinaryExprAST('<',$1,$3); }
|   exp "==" exp          { $$ = new BinaryExprAST('=',$1,$3); }

idexp:
    "id"                  { $$ = new VariableExprAST($1); }
|   "id" "(" optexp ")"   { $$ = new CallExprAST($1,$3); }
|   "id" "[" exp "]"      { $$ = new ArrayExprAST($1,$3); };        

optexp:
    %empty                { std::vector<ExprAST*> args;
			                $$ = args; }
|   explist               { $$ = $1; };

explist:
    exp                   { std::vector<ExprAST*> args;
                            args.push_back($1);
			                $$ = args;
                            }
|   exp "," explist       { $3.insert($3.begin(), $1); $$ = $3; };
 
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
