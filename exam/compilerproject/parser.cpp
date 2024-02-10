// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 44 "parser.yy"

# include "driver.hpp"

#line 50 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cpp"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< AssignmentAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< BlockAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.YY_MOVE_OR_COPY< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.YY_MOVE_OR_COPY< ForStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.YY_MOVE_OR_COPY< GlobalVarAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.YY_MOVE_OR_COPY< IfStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init: // init
        value.YY_MOVE_OR_COPY< InitFor* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.YY_MOVE_OR_COPY< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.YY_MOVE_OR_COPY< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< StmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding: // binding
        value.YY_MOVE_OR_COPY< VarBindingAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.YY_MOVE_OR_COPY< std::vector<StmtAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.YY_MOVE_OR_COPY< std::vector<VarBindingAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< BlockAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.move< ForStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.move< GlobalVarAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.move< IfStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init: // init
        value.move< InitFor* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< StmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding: // binding
        value.move< VarBindingAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<VarBindingAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.copy< AssignmentAST* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< BlockAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.copy< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.copy< ForStmtAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.copy< GlobalVarAST* > (that.value);
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.copy< IfStmtAST* > (that.value);
        break;

      case symbol_kind::S_init: // init
        value.copy< InitFor* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.copy< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.copy< RootAST* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< StmtAST* > (that.value);
        break;

      case symbol_kind::S_binding: // binding
        value.copy< VarBindingAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.copy< std::vector<StmtAST*> > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.copy< std::vector<VarBindingAST*> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentAST* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< BlockAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.move< ForStmtAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.move< GlobalVarAST* > (that.value);
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.move< IfStmtAST* > (that.value);
        break;

      case symbol_kind::S_init: // init
        value.move< InitFor* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< StmtAST* > (that.value);
        break;

      case symbol_kind::S_binding: // binding
        value.move< VarBindingAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<VarBindingAST*> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< AssignmentAST* > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< BlockAST* > ();
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        yylhs.value.emplace< ExprAST* > ();
        break;

      case symbol_kind::S_forstmt: // forstmt
        yylhs.value.emplace< ForStmtAST* > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< FunctionAST* > ();
        break;

      case symbol_kind::S_globalvar: // globalvar
        yylhs.value.emplace< GlobalVarAST* > ();
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        yylhs.value.emplace< IfStmtAST* > ();
        break;

      case symbol_kind::S_init: // init
        yylhs.value.emplace< InitFor* > ();
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        yylhs.value.emplace< PrototypeAST* > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        yylhs.value.emplace< RootAST* > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< StmtAST* > ();
        break;

      case symbol_kind::S_binding: // binding
        yylhs.value.emplace< VarBindingAST* > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case symbol_kind::S_stmts: // stmts
        yylhs.value.emplace< std::vector<StmtAST*> > ();
        break;

      case symbol_kind::S_vardefs: // vardefs
        yylhs.value.emplace< std::vector<VarBindingAST*> > ();
        break;

      case symbol_kind::S_idseq: // idseq
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // startsymb: program
#line 111 "parser.yy"
                        { drv.root = yystack_[0].value.as < RootAST* > (); }
#line 936 "parser.cpp"
    break;

  case 3: // program: %empty
#line 114 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(nullptr,nullptr); }
#line 942 "parser.cpp"
    break;

  case 4: // program: top ";" program
#line 115 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(yystack_[2].value.as < RootAST* > (),yystack_[0].value.as < RootAST* > ()); }
#line 948 "parser.cpp"
    break;

  case 5: // top: %empty
#line 118 "parser.yy"
                        { yylhs.value.as < RootAST* > () = nullptr; }
#line 954 "parser.cpp"
    break;

  case 6: // top: definition
#line 119 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < FunctionAST* > (); }
#line 960 "parser.cpp"
    break;

  case 7: // top: external
#line 120 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 966 "parser.cpp"
    break;

  case 8: // top: globalvar
#line 121 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < GlobalVarAST* > (); }
#line 972 "parser.cpp"
    break;

  case 9: // definition: "def" proto block
#line 124 "parser.yy"
                        { yylhs.value.as < FunctionAST* > () = new FunctionAST(yystack_[1].value.as < PrototypeAST* > (),yystack_[0].value.as < BlockAST* > ()); yystack_[1].value.as < PrototypeAST* > ()->noemit(); }
#line 978 "parser.cpp"
    break;

  case 10: // external: "extern" proto
#line 127 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 984 "parser.cpp"
    break;

  case 11: // proto: "id" "(" idseq ")"
#line 130 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = new PrototypeAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<std::string> > ());  }
#line 990 "parser.cpp"
    break;

  case 12: // globalvar: "global" "id"
#line 133 "parser.yy"
                        { yylhs.value.as < GlobalVarAST* > () = new GlobalVarAST(yystack_[0].value.as < std::string > ()); }
#line 996 "parser.cpp"
    break;

  case 13: // idseq: %empty
#line 136 "parser.yy"
                        { std::vector<std::string> args;
                         yylhs.value.as < std::vector<std::string> > () = args; }
#line 1003 "parser.cpp"
    break;

  case 14: // idseq: "id" idseq
#line 138 "parser.yy"
                        { yystack_[0].value.as < std::vector<std::string> > ().insert(yystack_[0].value.as < std::vector<std::string> > ().begin(),yystack_[1].value.as < std::string > ()); yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > (); }
#line 1009 "parser.cpp"
    break;

  case 15: // stmts: stmt
#line 146 "parser.yy"
                        { std::vector<StmtAST*> statements;
                          statements.push_back(yystack_[0].value.as < StmtAST* > ());
                          yylhs.value.as < std::vector<StmtAST*> > () = statements; }
#line 1017 "parser.cpp"
    break;

  case 16: // stmts: stmt ";" stmts
#line 149 "parser.yy"
                        { yystack_[0].value.as < std::vector<StmtAST*> > ().insert(yystack_[0].value.as < std::vector<StmtAST*> > ().begin(), yystack_[2].value.as < StmtAST* > ());
                          yylhs.value.as < std::vector<StmtAST*> > () = yystack_[0].value.as < std::vector<StmtAST*> > (); }
#line 1024 "parser.cpp"
    break;

  case 17: // stmt: assignment
#line 153 "parser.yy"
                        { yylhs.value.as < StmtAST* > () = yystack_[0].value.as < AssignmentAST* > (); }
#line 1030 "parser.cpp"
    break;

  case 18: // stmt: block
#line 154 "parser.yy"
                        { yylhs.value.as < StmtAST* > () = yystack_[0].value.as < BlockAST* > (); }
#line 1036 "parser.cpp"
    break;

  case 19: // stmt: ifstmt
#line 155 "parser.yy"
                        { yylhs.value.as < StmtAST* > () = yystack_[0].value.as < IfStmtAST* > (); }
#line 1042 "parser.cpp"
    break;

  case 20: // stmt: forstmt
#line 156 "parser.yy"
                        { yylhs.value.as < StmtAST* > () = yystack_[0].value.as < ForStmtAST* > (); }
#line 1048 "parser.cpp"
    break;

  case 21: // stmt: exp
#line 157 "parser.yy"
                        { yylhs.value.as < StmtAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1054 "parser.cpp"
    break;

  case 22: // assignment: "id" "=" exp
#line 160 "parser.yy"
                        {yylhs.value.as < AssignmentAST* > () = new AssignmentAST(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ExprAST* > ()); }
#line 1060 "parser.cpp"
    break;

  case 23: // assignment: "++" "id"
#line 161 "parser.yy"
                        {yylhs.value.as < AssignmentAST* > () = new AssignmentAST(yystack_[0].value.as < std::string > (),new BinaryExprAST('+',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1.0)));}
#line 1066 "parser.cpp"
    break;

  case 24: // assignment: "--" "id"
#line 162 "parser.yy"
                        {yylhs.value.as < AssignmentAST* > () = new AssignmentAST(yystack_[0].value.as < std::string > (),new BinaryExprAST('-',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1.0)));}
#line 1072 "parser.cpp"
    break;

  case 25: // assignment: "id" "[" exp "]" "=" exp
#line 163 "parser.yy"
                           {yylhs.value.as < AssignmentAST* > () = new ArrayAssignmentAST(yystack_[5].value.as < std::string > (), yystack_[3].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ());}
#line 1078 "parser.cpp"
    break;

  case 26: // block: "{" stmts "}"
#line 167 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[1].value.as < std::vector<StmtAST*> > ()); }
#line 1084 "parser.cpp"
    break;

  case 27: // block: "{" vardefs ";" stmts "}"
#line 168 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[3].value.as < std::vector<VarBindingAST*> > (),yystack_[1].value.as < std::vector<StmtAST*> > ()); }
#line 1090 "parser.cpp"
    break;

  case 28: // vardefs: binding
#line 171 "parser.yy"
                        { std::vector<VarBindingAST*> definitions;
                          definitions.push_back(yystack_[0].value.as < VarBindingAST* > ());
                          yylhs.value.as < std::vector<VarBindingAST*> > () = definitions; }
#line 1098 "parser.cpp"
    break;

  case 29: // vardefs: vardefs ";" binding
#line 174 "parser.yy"
                        { yystack_[2].value.as < std::vector<VarBindingAST*> > ().push_back(yystack_[0].value.as < VarBindingAST* > ()); yylhs.value.as < std::vector<VarBindingAST*> > () = yystack_[2].value.as < std::vector<VarBindingAST*> > (); }
#line 1104 "parser.cpp"
    break;

  case 30: // binding: "var" "id" initexp
#line 177 "parser.yy"
                        { yylhs.value.as < VarBindingAST* > () = new VarBindingAST(yystack_[1].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ());}
#line 1110 "parser.cpp"
    break;

  case 31: // binding: "var" "id" "[" "number" "]"
#line 178 "parser.yy"
                              { yylhs.value.as < VarBindingAST* > () = new ArrayDeclarationAST(yystack_[3].value.as < std::string > (), atoi(yystack_[1].value.as < double > ().c_str())); }
#line 1116 "parser.cpp"
    break;

  case 32: // binding: "var" "id" "[" "number" "]" "=" "{" explist "}"
#line 179 "parser.yy"
                                                   { yylhs.value.as < VarBindingAST* > () = new ArrayDeclarationAST(yystack_[7].value.as < std::string > (),yystack_[5].value.as < double > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1122 "parser.cpp"
    break;

  case 33: // exp: exp "+" exp
#line 182 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('+',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1128 "parser.cpp"
    break;

  case 34: // exp: exp "-" exp
#line 183 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1134 "parser.cpp"
    break;

  case 35: // exp: exp "*" exp
#line 184 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('*',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1140 "parser.cpp"
    break;

  case 36: // exp: exp "/" exp
#line 185 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('/',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1146 "parser.cpp"
    break;

  case 37: // exp: idexp
#line 186 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1152 "parser.cpp"
    break;

  case 38: // exp: "(" exp ")"
#line 187 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1158 "parser.cpp"
    break;

  case 39: // exp: "-" exp
#line 188 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('*',yystack_[0].value.as < ExprAST* > (), new NumberExprAST(-1.0)); }
#line 1164 "parser.cpp"
    break;

  case 40: // exp: "number"
#line 189 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new NumberExprAST(yystack_[0].value.as < double > ()); }
#line 1170 "parser.cpp"
    break;

  case 41: // exp: expif
#line 190 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1176 "parser.cpp"
    break;

  case 42: // initexp: %empty
#line 193 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = nullptr; }
#line 1182 "parser.cpp"
    break;

  case 43: // initexp: "=" exp
#line 194 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1188 "parser.cpp"
    break;

  case 44: // expif: condexp "?" exp ":" exp
#line 197 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new IfExprAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1194 "parser.cpp"
    break;

  case 45: // condexp: relexp
#line 200 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1200 "parser.cpp"
    break;

  case 46: // condexp: relexp "and" relexp
#line 201 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new LogicalExprAST("and",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1206 "parser.cpp"
    break;

  case 47: // condexp: relexp "or" relexp
#line 202 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new LogicalExprAST("or", yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1212 "parser.cpp"
    break;

  case 48: // condexp: "not" condexp
#line 203 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new LogicalExprAST("not", yystack_[0].value.as < ExprAST* > ()); }
#line 1218 "parser.cpp"
    break;

  case 49: // condexp: "(" condexp ")"
#line 204 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1224 "parser.cpp"
    break;

  case 50: // relexp: exp "<" exp
#line 208 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('<',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1230 "parser.cpp"
    break;

  case 51: // relexp: exp ">" exp
#line 209 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('>',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1236 "parser.cpp"
    break;

  case 52: // relexp: exp "==" exp
#line 210 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('=',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1242 "parser.cpp"
    break;

  case 53: // idexp: "id"
#line 213 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ()); }
#line 1248 "parser.cpp"
    break;

  case 54: // idexp: "id" "(" optexp ")"
#line 214 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1254 "parser.cpp"
    break;

  case 55: // idexp: "id" "[" exp "]"
#line 215 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new ArrayAccessExprAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > ());}
#line 1260 "parser.cpp"
    break;

  case 56: // optexp: %empty
#line 219 "parser.yy"
                        { std::vector<ExprAST*> args;
			                    yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1267 "parser.cpp"
    break;

  case 57: // optexp: explist
#line 221 "parser.yy"
                        { yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1273 "parser.cpp"
    break;

  case 58: // explist: exp
#line 224 "parser.yy"
                        { std::vector<ExprAST*> args; args.push_back(yystack_[0].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = args;}
#line 1279 "parser.cpp"
    break;

  case 59: // explist: exp "," explist
#line 225 "parser.yy"
                        { yystack_[0].value.as < std::vector<ExprAST*> > ().insert(yystack_[0].value.as < std::vector<ExprAST*> > ().begin(), yystack_[2].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1285 "parser.cpp"
    break;

  case 60: // ifstmt: "if" "(" condexp ")" stmt
#line 230 "parser.yy"
                                                     { yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < StmtAST* > ()); }
#line 1291 "parser.cpp"
    break;

  case 61: // ifstmt: "if" "(" condexp ")" stmt "else" stmt
#line 231 "parser.yy"
                                                     { yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[4].value.as < ExprAST* > (), yystack_[2].value.as < StmtAST* > (), yystack_[0].value.as < StmtAST* > ()); }
#line 1297 "parser.cpp"
    break;

  case 62: // init: binding
#line 234 "parser.yy"
                       { yylhs.value.as < InitFor* > () = new InitFor(yystack_[0].value.as < VarBindingAST* > ()); }
#line 1303 "parser.cpp"
    break;

  case 63: // init: assignment
#line 235 "parser.yy"
                       { yylhs.value.as < InitFor* > () = new InitFor(yystack_[0].value.as < AssignmentAST* > ()); }
#line 1309 "parser.cpp"
    break;

  case 64: // forstmt: "for" "(" init ";" condexp ";" assignment ")" stmt
#line 238 "parser.yy"
                                                     { yylhs.value.as < ForStmtAST* > () = new ForStmtAST(yystack_[6].value.as < InitFor* > (), yystack_[4].value.as < ExprAST* > (), yystack_[2].value.as < AssignmentAST* > (), yystack_[0].value.as < StmtAST* > ());}
#line 1315 "parser.cpp"
    break;


#line 1319 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -101;

  const signed char parser::yytable_ninf_ = -46;

  const short
  parser::yypact_[] =
  {
      59,     4,     4,    25,    75,  -101,    76,  -101,  -101,  -101,
      77,  -101,    80,  -101,  -101,    59,    63,    85,  -101,  -101,
      63,    89,    29,    78,    82,    29,    88,   110,   117,    29,
     100,  -101,   112,   146,  -101,  -101,   155,  -101,   164,  -101,
     149,    40,  -101,  -101,  -101,  -101,  -101,    -7,   114,  -101,
    -101,   138,   124,    -6,    29,    10,   164,   149,    29,    29,
      29,  -101,    95,    85,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,  -101,  -101,    29,   127,  -101,
     126,    -5,  -101,  -101,   160,   125,   152,  -101,   164,     5,
    -101,   156,  -101,   114,   114,  -101,  -101,   164,   164,   164,
     151,    -4,    -4,    48,   164,   137,    95,    29,    29,    29,
    -101,   154,  -101,    29,  -101,   157,   158,    61,    16,  -101,
      29,   164,   159,    95,   154,    66,   164,    29,  -101,   165,
     162,    95,  -101,  -101
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     0,     6,     7,     8,
       0,    10,     0,    12,     1,     3,    13,     0,     9,     4,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,    40,     0,    15,    17,    18,     0,    28,    21,    41,
       0,    45,    37,    19,    20,    14,    11,    53,    39,    24,
      23,     0,     0,    42,     0,     0,     0,    48,    56,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    49,     0,     0,    30,
       0,     0,    63,    62,     0,    58,     0,    57,    22,     0,
      16,     0,    29,    34,    33,    35,    36,    50,    51,    52,
       0,    46,    47,     0,    43,     0,     0,     0,     0,     0,
      54,    55,    27,     0,    55,    31,    60,     0,     0,    59,
       0,    44,     0,     0,     0,     0,    25,     0,    61,     0,
       0,     0,    32,    64
  };

  const short
  parser::yypgoto_[] =
  {
    -101,  -101,   168,  -101,  -101,  -101,   183,  -101,   166,    83,
    -100,   -53,   175,  -101,   -47,   -22,  -101,  -101,   -24,    79,
    -101,  -101,   -20,  -101,  -101,  -101
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,    11,     9,    21,    32,
      33,    34,    35,    36,    37,    38,    79,    39,    40,    41,
      42,    86,    87,    43,    84,    44
  };

  const short
  parser::yytable_[] =
  {
      48,    52,    82,    51,    58,    57,   116,    56,    83,   -45,
      64,    65,    77,    59,    66,    67,    92,    23,    24,   125,
      68,    69,    70,   128,    72,    73,    74,    78,   107,    71,
      80,   133,    56,    26,    22,    10,    85,    88,    89,   111,
      25,    81,    93,    94,    95,    96,    97,    98,    99,   100,
      56,    56,   103,    64,    65,   104,    13,    66,    67,    29,
      47,    31,    -5,    68,    69,    70,    64,    65,    72,    73,
      66,    67,   129,    23,    24,    14,    68,    69,    70,    15,
       1,     2,   114,     3,   118,   117,    56,    85,    16,   119,
      22,   121,    23,    24,    20,   124,    25,    81,   126,    17,
      22,    46,    23,    24,    17,    85,    25,   130,    26,    49,
      27,    58,    28,    50,    17,    29,    30,    31,    59,    53,
      27,    54,    28,    66,    67,    29,    30,    31,    55,   109,
      64,    65,    61,    60,    66,    67,    76,    71,   106,    71,
      68,    69,    70,    64,    65,    90,    91,    66,    67,    62,
      75,   101,   102,    68,    69,    70,    64,    65,    63,   105,
      66,    67,    71,   108,   110,   113,    68,    69,    70,    64,
      65,   115,   120,    66,    67,   122,   112,   131,   127,    68,
      69,    70,   132,    19,   123,    12,    45,    18
  };

  const unsigned char
  parser::yycheck_[] =
  {
      22,    25,    55,    25,    11,    29,   106,    29,    55,    13,
       5,     6,    18,    18,     9,    10,    63,     7,     8,     3,
      15,    16,    17,   123,    28,    29,    33,    33,    33,    13,
      54,   131,    54,    23,     5,    31,    58,    59,    60,    34,
      11,    31,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     5,     6,    77,    31,     9,    10,    30,
      31,    32,     3,    15,    16,    17,     5,     6,    28,    29,
       9,    10,   125,     7,     8,     0,    15,    16,    17,     3,
      21,    22,    34,    24,   108,   107,   108,   109,    11,   109,
       5,   113,     7,     8,    31,    34,    11,    31,   120,    19,
       5,    12,     7,     8,    19,   127,    11,   127,    23,    31,
      25,    11,    27,    31,    19,    30,    31,    32,    18,    31,
      25,    11,    27,     9,    10,    30,    31,    32,    11,     4,
       5,     6,    20,    33,     9,    10,    12,    13,    12,    13,
      15,    16,    17,     5,     6,    62,    63,     9,    10,     3,
      12,    72,    73,    15,    16,    17,     5,     6,     3,    32,
       9,    10,    13,     3,    12,    14,    15,    16,    17,     5,
       6,    34,    18,     9,    10,    18,    20,    12,    19,    15,
      16,    17,    20,    15,    26,     2,    20,    12
  };

  const signed char
  parser::yystos_[] =
  {
       0,    21,    22,    24,    36,    37,    38,    39,    40,    42,
      31,    41,    41,    31,     0,     3,    11,    19,    47,    37,
      31,    43,     5,     7,     8,    11,    23,    25,    27,    30,
      31,    32,    44,    45,    46,    47,    48,    49,    50,    52,
      53,    54,    55,    58,    60,    43,    12,    31,    50,    31,
      31,    50,    53,    31,    11,    11,    50,    53,    11,    18,
      33,    20,     3,     3,     5,     6,     9,    10,    15,    16,
      17,    13,    28,    29,    33,    12,    12,    18,    33,    51,
      53,    31,    46,    49,    59,    50,    56,    57,    50,    50,
      44,    44,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    54,    54,    50,    50,    32,    12,    33,     3,     4,
      12,    34,    20,    14,    34,    34,    45,    50,    53,    57,
      18,    50,    18,    26,    34,     3,    50,    19,    45,    46,
      57,    12,    20,    45
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    38,    39,
      40,    41,    42,    43,    43,    44,    44,    45,    45,    45,
      45,    45,    46,    46,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    51,    51,    52,    53,    53,    53,    53,    53,
      54,    54,    54,    55,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     3,
       2,     4,     2,     0,     2,     1,     3,     1,     1,     1,
       1,     1,     3,     2,     2,     6,     3,     5,     1,     3,
       3,     5,     9,     3,     3,     3,     3,     1,     3,     2,
       1,     1,     0,     2,     5,     1,     3,     3,     2,     3,
       3,     3,     3,     1,     4,     4,     0,     1,     1,     3,
       5,     7,     1,     1,     9
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\";\"", "\",\"",
  "\"-\"", "\"+\"", "\"--\"", "\"++\"", "\"*\"", "\"/\"", "\"(\"", "\")\"",
  "\"?\"", "\":\"", "\"<\"", "\">\"", "\"==\"", "\"=\"", "\"{\"", "\"}\"",
  "\"extern\"", "\"def\"", "\"var\"", "\"global\"", "\"if\"", "\"else\"",
  "\"for\"", "\"and\"", "\"or\"", "\"not\"", "\"id\"", "\"number\"",
  "\"[\"", "\"]\"", "$accept", "startsymb", "program", "top", "definition",
  "external", "proto", "globalvar", "idseq", "stmts", "stmt", "assignment",
  "block", "vardefs", "binding", "exp", "initexp", "expif", "condexp",
  "relexp", "idexp", "optexp", "explist", "ifstmt", "init", "forstmt", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   111,   111,   114,   115,   118,   119,   120,   121,   124,
     127,   130,   133,   136,   138,   146,   149,   153,   154,   155,
     156,   157,   160,   161,   162,   163,   167,   168,   171,   174,
     177,   178,   179,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   193,   194,   197,   200,   201,   202,   203,   204,
     208,   209,   210,   213,   214,   215,   219,   221,   224,   225,
     230,   231,   234,   235,   238
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1882 "parser.cpp"

#line 240 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}


%nonassoc;
| "-" exp %perc INVERT
