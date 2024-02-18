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

      case symbol_kind::S_binding: // binding
        value.YY_MOVE_OR_COPY< BindingAST* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< InitAST* > (YY_MOVE (that.value));
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

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.YY_MOVE_OR_COPY< std::vector<BindingAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.YY_MOVE_OR_COPY< std::vector<StmtAST*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_binding: // binding
        value.move< BindingAST* > (YY_MOVE (that.value));
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
        value.move< InitAST* > (YY_MOVE (that.value));
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

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<BindingAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_binding: // binding
        value.copy< BindingAST* > (that.value);
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
        value.copy< InitAST* > (that.value);
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

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.copy< std::vector<BindingAST*> > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.copy< std::vector<StmtAST*> > (that.value);
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

      case symbol_kind::S_binding: // binding
        value.move< BindingAST* > (that.value);
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
        value.move< InitAST* > (that.value);
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

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<BindingAST*> > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (that.value);
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

      case symbol_kind::S_binding: // binding
        yylhs.value.emplace< BindingAST* > ();
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
        yylhs.value.emplace< InitAST* > ();
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

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_vardefs: // vardefs
        yylhs.value.emplace< std::vector<BindingAST*> > ();
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case symbol_kind::S_stmts: // stmts
        yylhs.value.emplace< std::vector<StmtAST*> > ();
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
#line 119 "parser.yy"
                          { yylhs.value.as < RootAST* > () = nullptr; }
#line 954 "parser.cpp"
    break;

  case 6: // top: definition
#line 120 "parser.yy"
                          { yylhs.value.as < RootAST* > () = yystack_[0].value.as < FunctionAST* > (); }
#line 960 "parser.cpp"
    break;

  case 7: // top: external
#line 121 "parser.yy"
                          { yylhs.value.as < RootAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 966 "parser.cpp"
    break;

  case 8: // top: globalvar
#line 122 "parser.yy"
                          { yylhs.value.as < RootAST* > () = yystack_[0].value.as < GlobalVarAST* > (); }
#line 972 "parser.cpp"
    break;

  case 9: // definition: "def" proto block
#line 125 "parser.yy"
                            { yylhs.value.as < FunctionAST* > () = new FunctionAST(yystack_[1].value.as < PrototypeAST* > (),yystack_[0].value.as < BlockAST* > ()); yystack_[1].value.as < PrototypeAST* > ()->noemit(); }
#line 978 "parser.cpp"
    break;

  case 10: // external: "extern" proto
#line 128 "parser.yy"
                          { yylhs.value.as < PrototypeAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 984 "parser.cpp"
    break;

  case 11: // proto: "id" "(" idseq ")"
#line 131 "parser.yy"
                          { yylhs.value.as < PrototypeAST* > () = new PrototypeAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<std::string> > ());  }
#line 990 "parser.cpp"
    break;

  case 12: // globalvar: "global" "id"
#line 134 "parser.yy"
                                        { yylhs.value.as < GlobalVarAST* > () = new GlobalVarAST(yystack_[0].value.as < std::string > ()); }
#line 996 "parser.cpp"
    break;

  case 13: // globalvar: "global" "id" "[" "number" "]"
#line 135 "parser.yy"
                                        { yylhs.value.as < GlobalVarAST* > () = new GlobalArrayAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > ()); }
#line 1002 "parser.cpp"
    break;

  case 14: // idseq: %empty
#line 139 "parser.yy"
                          { std::vector<std::string> args;
                         yylhs.value.as < std::vector<std::string> > () = args; }
#line 1009 "parser.cpp"
    break;

  case 15: // idseq: "id" idseq
#line 141 "parser.yy"
                          { yystack_[0].value.as < std::vector<std::string> > ().insert(yystack_[0].value.as < std::vector<std::string> > ().begin(),yystack_[1].value.as < std::string > ()); yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > (); }
#line 1015 "parser.cpp"
    break;

  case 16: // stmts: stmt
#line 152 "parser.yy"
                           { std::vector<StmtAST*> stmts;
                            stmts.insert(stmts.begin(), yystack_[0].value.as < StmtAST* > ());
                            yylhs.value.as < std::vector<StmtAST*> > () = stmts; }
#line 1023 "parser.cpp"
    break;

  case 17: // stmts: stmt ";" stmts
#line 155 "parser.yy"
                          { yystack_[0].value.as < std::vector<StmtAST*> > ().insert(yystack_[0].value.as < std::vector<StmtAST*> > ().begin(), yystack_[2].value.as < StmtAST* > ());
                            yylhs.value.as < std::vector<StmtAST*> > () = yystack_[0].value.as < std::vector<StmtAST*> > (); }
#line 1030 "parser.cpp"
    break;

  case 18: // stmt: assignment
#line 159 "parser.yy"
                          { yylhs.value.as < StmtAST* > () = new StmtAST(yystack_[0].value.as < AssignmentAST* > ()); }
#line 1036 "parser.cpp"
    break;

  case 19: // stmt: block
#line 160 "parser.yy"
                          { yylhs.value.as < StmtAST* > () = new StmtAST(yystack_[0].value.as < BlockAST* > ()); }
#line 1042 "parser.cpp"
    break;

  case 20: // stmt: ifstmt
#line 161 "parser.yy"
                          { yylhs.value.as < StmtAST* > () = new StmtAST(yystack_[0].value.as < IfStmtAST* > ()); }
#line 1048 "parser.cpp"
    break;

  case 21: // stmt: forstmt
#line 162 "parser.yy"
                          { yylhs.value.as < StmtAST* > () = new StmtAST(yystack_[0].value.as < ForStmtAST* > ()); }
#line 1054 "parser.cpp"
    break;

  case 22: // stmt: exp
#line 163 "parser.yy"
                          { yylhs.value.as < StmtAST* > () = new StmtAST(yystack_[0].value.as < ExprAST* > ()); }
#line 1060 "parser.cpp"
    break;

  case 23: // forstmt: "for" "(" init ";" condexp ";" assignment ")" stmt
#line 166 "parser.yy"
                                                        {yylhs.value.as < ForStmtAST* > () = new ForStmtAST(yystack_[6].value.as < InitAST* > (),yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < AssignmentAST* > (),yystack_[0].value.as < StmtAST* > ()); }
#line 1066 "parser.cpp"
    break;

  case 24: // init: binding
#line 169 "parser.yy"
                            { yylhs.value.as < InitAST* > () = yystack_[0].value.as < BindingAST* > (); }
#line 1072 "parser.cpp"
    break;

  case 25: // init: assignment
#line 170 "parser.yy"
                            { yylhs.value.as < InitAST* > () = yystack_[0].value.as < AssignmentAST* > (); }
#line 1078 "parser.cpp"
    break;

  case 26: // assignment: "-" "-" "id"
#line 173 "parser.yy"
                                    { yylhs.value.as < AssignmentAST* > () = new VarAssignmentAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('-',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1.0)));}
#line 1084 "parser.cpp"
    break;

  case 27: // assignment: "+" "+" "id"
#line 174 "parser.yy"
                                    { yylhs.value.as < AssignmentAST* > () = new VarAssignmentAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('+',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1.0)));}
#line 1090 "parser.cpp"
    break;

  case 28: // assignment: "id" "=" exp
#line 175 "parser.yy"
                                    { yylhs.value.as < AssignmentAST* > () = new VarAssignmentAST(yystack_[2].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1096 "parser.cpp"
    break;

  case 29: // assignment: "id" "[" exp "]" "=" exp
#line 176 "parser.yy"
                                    { yylhs.value.as < AssignmentAST* > () = new ArrayAssignmentAST(yystack_[5].value.as < std::string > (),yystack_[3].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1102 "parser.cpp"
    break;

  case 30: // block: "{" stmts "}"
#line 180 "parser.yy"
                              { std::vector<BindingAST*> tmp; 
                                yylhs.value.as < BlockAST* > () = new BlockAST(tmp, yystack_[1].value.as < std::vector<StmtAST*> > ());}
#line 1109 "parser.cpp"
    break;

  case 31: // block: "{" vardefs ";" stmts "}"
#line 182 "parser.yy"
                              { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[3].value.as < std::vector<BindingAST*> > (),yystack_[1].value.as < std::vector<StmtAST*> > ()); }
#line 1115 "parser.cpp"
    break;

  case 32: // vardefs: binding
#line 185 "parser.yy"
                            { std::vector<BindingAST*> definitions;
                            definitions.push_back(yystack_[0].value.as < BindingAST* > ());
                            yylhs.value.as < std::vector<BindingAST*> > () = definitions; }
#line 1123 "parser.cpp"
    break;

  case 33: // vardefs: vardefs ";" binding
#line 188 "parser.yy"
                            { yystack_[2].value.as < std::vector<BindingAST*> > ().push_back(yystack_[0].value.as < BindingAST* > ());
                            yylhs.value.as < std::vector<BindingAST*> > () = yystack_[2].value.as < std::vector<BindingAST*> > (); }
#line 1130 "parser.cpp"
    break;

  case 34: // binding: "var" "id" initexp
#line 192 "parser.yy"
                                                        { yylhs.value.as < BindingAST* > () = new VarBindingAST(yystack_[1].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1136 "parser.cpp"
    break;

  case 35: // binding: "var" "id" "[" "number" "]"
#line 193 "parser.yy"
                                                        { yylhs.value.as < BindingAST* > () = new ArrayBindingAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > ()); }
#line 1142 "parser.cpp"
    break;

  case 36: // binding: "var" "id" "[" "number" "]" "=" "{" explist "}"
#line 194 "parser.yy"
                                                      { yylhs.value.as < BindingAST* > () = new ArrayBindingAST(yystack_[7].value.as < std::string > (),yystack_[5].value.as < double > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1148 "parser.cpp"
    break;

  case 37: // exp: exp "+" exp
#line 198 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('+',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1154 "parser.cpp"
    break;

  case 38: // exp: exp "-" exp
#line 199 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1160 "parser.cpp"
    break;

  case 39: // exp: exp "*" exp
#line 200 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('*',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1166 "parser.cpp"
    break;

  case 40: // exp: exp "/" exp
#line 201 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('/',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1172 "parser.cpp"
    break;

  case 41: // exp: "-" idexp
#line 202 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',new NumberExprAST(0.0),yystack_[0].value.as < ExprAST* > ()); }
#line 1178 "parser.cpp"
    break;

  case 42: // exp: idexp
#line 203 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1184 "parser.cpp"
    break;

  case 43: // exp: "(" exp ")"
#line 204 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1190 "parser.cpp"
    break;

  case 44: // exp: "number"
#line 205 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new NumberExprAST(yystack_[0].value.as < double > ()); }
#line 1196 "parser.cpp"
    break;

  case 45: // exp: "-" "number"
#line 206 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',new NumberExprAST(0.0),new NumberExprAST(yystack_[0].value.as < double > ())); }
#line 1202 "parser.cpp"
    break;

  case 46: // exp: expif
#line 207 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1208 "parser.cpp"
    break;

  case 47: // initexp: %empty
#line 210 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new NumberExprAST(0.0); }
#line 1214 "parser.cpp"
    break;

  case 48: // initexp: "=" exp
#line 211 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1220 "parser.cpp"
    break;

  case 49: // expif: condexp "?" exp ":" exp
#line 214 "parser.yy"
                            { yylhs.value.as < ExprAST* > () = new IfExprAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1226 "parser.cpp"
    break;

  case 50: // ifstmt: "if" "(" condexp ")" stmt
#line 217 "parser.yy"
                                            { yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < StmtAST* > (),nullptr); }
#line 1232 "parser.cpp"
    break;

  case 51: // ifstmt: "if" "(" condexp ")" stmt "else" stmt
#line 218 "parser.yy"
                                            { yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < StmtAST* > (),yystack_[0].value.as < StmtAST* > ()); }
#line 1238 "parser.cpp"
    break;

  case 52: // condexp: relexp
#line 221 "parser.yy"
                                { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1244 "parser.cpp"
    break;

  case 53: // condexp: relexp "and" condexp
#line 222 "parser.yy"
                                { yylhs.value.as < ExprAST* > () = new BinaryExprAST('&',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1250 "parser.cpp"
    break;

  case 54: // condexp: relexp "or" condexp
#line 223 "parser.yy"
                                { yylhs.value.as < ExprAST* > () = new BinaryExprAST('|',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1256 "parser.cpp"
    break;

  case 55: // condexp: "not" condexp
#line 224 "parser.yy"
                                { yylhs.value.as < ExprAST* > () = new UnaryExprAST('!',yystack_[0].value.as < ExprAST* > ()); }
#line 1262 "parser.cpp"
    break;

  case 56: // condexp: "(" condexp ")"
#line 225 "parser.yy"
                                { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1268 "parser.cpp"
    break;

  case 57: // relexp: exp "<" exp
#line 228 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('<',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1274 "parser.cpp"
    break;

  case 58: // relexp: exp "==" exp
#line 229 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new BinaryExprAST('=',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1280 "parser.cpp"
    break;

  case 59: // idexp: "id"
#line 232 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ()); }
#line 1286 "parser.cpp"
    break;

  case 60: // idexp: "id" "(" optexp ")"
#line 233 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1292 "parser.cpp"
    break;

  case 61: // idexp: "id" "[" exp "]"
#line 234 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new ArrayExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < ExprAST* > ()); }
#line 1298 "parser.cpp"
    break;

  case 62: // optexp: %empty
#line 237 "parser.yy"
                          { std::vector<ExprAST*> args;
			                yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1305 "parser.cpp"
    break;

  case 63: // optexp: explist
#line 239 "parser.yy"
                          { yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1311 "parser.cpp"
    break;

  case 64: // explist: exp
#line 242 "parser.yy"
                          { std::vector<ExprAST*> args;
                            args.push_back(yystack_[0].value.as < ExprAST* > ());
			                yylhs.value.as < std::vector<ExprAST*> > () = args;
                            }
#line 1320 "parser.cpp"
    break;

  case 65: // explist: exp "," explist
#line 246 "parser.yy"
                          { yystack_[0].value.as < std::vector<ExprAST*> > ().insert(yystack_[0].value.as < std::vector<ExprAST*> > ().begin(), yystack_[2].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1326 "parser.cpp"
    break;


#line 1330 "parser.cpp"

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


  const signed char parser::yypact_ninf_ = -108;

  const signed char parser::yytable_ninf_ = -6;

  const short
  parser::yypact_[] =
  {
      83,   -22,   -22,   -11,    24,  -108,    23,  -108,  -108,  -108,
      45,  -108,    49,    66,  -108,    83,    37,    50,  -108,    70,
    -108,    37,    84,     9,    99,     0,    81,   124,   125,     0,
       3,  -108,   118,   138,  -108,  -108,  -108,   139,  -108,   162,
    -108,  -108,   133,    69,  -108,   134,  -108,  -108,   131,     4,
    -108,  -108,   141,    47,   142,    88,    53,     0,     5,   162,
    -108,     0,     0,     0,  -108,    86,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -108,  -108,     0,  -108,
    -108,  -108,     0,   112,  -108,    98,   149,    67,   159,  -108,
    -108,    56,   153,  -108,   162,   113,  -108,   155,  -108,   106,
     106,  -108,  -108,   162,   162,   152,  -108,  -108,   117,   162,
     154,    86,     0,     0,     0,  -108,   163,  -108,     0,  -108,
     164,   156,   132,    12,  -108,     0,   162,   158,    86,   163,
      11,   162,     0,  -108,   167,   165,    86,  -108,  -108
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     0,     6,     7,     8,
       0,    10,     0,    12,     1,     3,    14,     0,     9,     0,
       4,    14,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    44,     0,    16,    21,    18,    19,     0,    32,    22,
      46,    20,     0,    52,    42,     0,    15,    11,     0,    59,
      45,    41,     0,     0,     0,     0,    47,     0,     0,     0,
      55,    62,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    26,     0,    27,
      43,    56,     0,     0,    34,     0,     0,     0,     0,    25,
      24,    64,     0,    63,    28,     0,    17,     0,    33,    38,
      37,    39,    40,    57,    58,     0,    53,    54,     0,    48,
       0,     0,     0,     0,     0,    60,    61,    31,     0,    61,
      35,    50,     0,     0,    65,     0,    49,     0,     0,     0,
       0,    29,     0,    51,     0,     0,     0,    36,    23
  };

  const short
  parser::yypgoto_[] =
  {
    -108,  -108,   168,  -108,  -108,  -108,   178,  -108,   166,    63,
     -53,  -108,  -108,   -57,   172,  -108,   -38,   -25,  -108,  -108,
    -108,   -23,  -108,   -20,  -108,  -107
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,    11,     9,    22,    32,
      33,    34,    88,    35,    36,    37,    38,    39,    84,    40,
      41,    42,    43,    44,    92,    93
  };

  const short
  parser::yytable_[] =
  {
      54,    89,    55,    51,    59,    53,    60,   124,    10,    25,
      86,    24,    61,    61,    48,   130,    86,    24,    62,    13,
      90,    63,    78,    73,    14,   135,    15,    26,    98,    29,
      49,    31,    59,    51,    85,    87,    91,    94,    95,    49,
      50,    87,    99,   100,   101,   102,   103,   104,   105,    59,
      59,   106,   107,   108,    16,    23,    24,   109,   121,    25,
     114,    67,    68,    69,    70,    17,    17,    21,    82,    71,
      72,    83,    26,   134,    27,   133,    28,    49,    50,    29,
      30,    31,    62,   138,    19,   112,    -5,   122,    59,    91,
     123,    23,    24,   126,    47,    25,    74,    75,    81,    73,
     131,    45,    17,     1,     2,    52,     3,    91,   111,    73,
      27,    56,    28,    69,    70,    29,    30,    31,    67,    68,
      69,    70,    67,    68,    69,    70,    71,    72,    96,    97,
      71,    72,   116,    57,    58,    64,   119,    67,    68,    69,
      70,    65,    66,   110,    73,    71,    72,    67,    68,    69,
      70,   129,    80,    76,    48,    71,    72,    67,    68,    69,
      70,    77,   113,   115,   118,    71,    72,    67,    68,    69,
      70,    79,   117,   120,   132,    71,    72,   136,   125,   127,
      12,   128,   137,    20,    18,     0,     0,    46
  };

  const short
  parser::yycheck_[] =
  {
      25,    58,    25,    23,    29,     5,    29,   114,    30,     9,
       5,     6,     9,     9,     5,     3,     5,     6,    15,    30,
      58,    18,    18,    11,     0,   132,     3,    22,    66,    29,
      30,    31,    57,    53,    57,    30,    61,    62,    63,    30,
      31,    30,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    74,    75,    78,     9,     5,     6,    82,   111,     9,
       4,     5,     6,     7,     8,    16,    16,    30,    15,    13,
      14,    18,    22,   130,    24,   128,    26,    30,    31,    29,
      30,    31,    15,   136,    18,    18,     3,   112,   113,   114,
     113,     5,     6,   118,    10,     9,    27,    28,    10,    11,
     125,    31,    16,    20,    21,     6,    23,   132,    10,    11,
      24,    30,    26,     7,     8,    29,    30,    31,     5,     6,
       7,     8,     5,     6,     7,     8,    13,    14,    65,    66,
      13,    14,    19,     9,     9,    17,    19,     5,     6,     7,
       8,     3,     3,    31,    11,    13,    14,     5,     6,     7,
       8,    19,    10,    19,     5,    13,    14,     5,     6,     7,
       8,    30,     3,    10,    12,    13,    14,     5,     6,     7,
       8,    30,    17,    19,    16,    13,    14,    10,    15,    15,
       2,    25,    17,    15,    12,    -1,    -1,    21
  };

  const signed char
  parser::yystos_[] =
  {
       0,    20,    21,    23,    33,    34,    35,    36,    37,    39,
      30,    38,    38,    30,     0,     3,     9,    16,    46,    18,
      34,    30,    40,     5,     6,     9,    22,    24,    26,    29,
      30,    31,    41,    42,    43,    45,    46,    47,    48,    49,
      51,    52,    53,    54,    55,    31,    40,    10,     5,    30,
      31,    55,     6,     5,    49,    53,    30,     9,     9,    49,
      53,     9,    15,    18,    17,     3,     3,     5,     6,     7,
       8,    13,    14,    11,    27,    28,    19,    30,    18,    30,
      10,    10,    15,    18,    50,    53,     5,    30,    44,    45,
      48,    49,    56,    57,    49,    49,    41,    41,    48,    49,
      49,    49,    49,    49,    49,    49,    53,    53,    49,    49,
      31,    10,    18,     3,     4,    10,    19,    17,    12,    19,
      19,    42,    49,    53,    57,    15,    49,    15,    25,    19,
       3,    49,    16,    42,    45,    57,    10,    17,    42
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    35,    35,    35,    35,    36,
      37,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    42,    43,    44,    44,    45,    45,    45,    45,
      46,    46,    47,    47,    48,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    51,
      52,    52,    53,    53,    53,    53,    53,    54,    54,    55,
      55,    55,    56,    56,    57,    57
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     3,
       2,     4,     2,     5,     0,     2,     1,     3,     1,     1,
       1,     1,     1,     9,     1,     1,     3,     3,     3,     6,
       3,     5,     1,     3,     3,     5,     9,     3,     3,     3,
       3,     2,     1,     3,     1,     2,     1,     0,     2,     5,
       5,     7,     1,     3,     3,     2,     3,     3,     3,     1,
       4,     4,     0,     1,     1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\";\"", "\",\"",
  "\"-\"", "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"?\"", "\":\"",
  "\"<\"", "\"==\"", "\"=\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"",
  "\"extern\"", "\"def\"", "\"var\"", "\"global\"", "\"if\"", "\"else\"",
  "\"for\"", "\"and\"", "\"or\"", "\"not\"", "\"id\"", "\"number\"",
  "$accept", "startsymb", "program", "top", "definition", "external",
  "proto", "globalvar", "idseq", "stmts", "stmt", "forstmt", "init",
  "assignment", "block", "vardefs", "binding", "exp", "initexp", "expif",
  "ifstmt", "condexp", "relexp", "idexp", "optexp", "explist", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   111,   111,   114,   115,   119,   120,   121,   122,   125,
     128,   131,   134,   135,   139,   141,   152,   155,   159,   160,
     161,   162,   163,   166,   169,   170,   173,   174,   175,   176,
     180,   182,   185,   188,   192,   193,   194,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   210,   211,   214,
     217,   218,   221,   222,   223,   224,   225,   228,   229,   232,
     233,   234,   237,   239,   242,   246
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
#line 1893 "parser.cpp"

#line 248 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
