
#include "Action.h"
#include "Env.h"
#include "Id.h"
#include "Lexer.h"
#include "Stack.h"
#include "State.h"
#include "UnitSet.h"

using namespace bin;
using namespace lexer;
using namespace symbols;

#ifndef _PARSER_H_
#define _PARSER_H_

namespace parser {

class Parser {

public:
  Parser();
  ~Parser();

  bool Build(const char*, const char*);
  bool Analyze(const char*);

private:
  // symbols
  Env *env;
  // lexer
  Word *lok;
  lexer::Lexer *lex;
  // parser
  Action *action_table;
  Stack<State*> e_stack;
  std::vector<std::function<Unit*()> > reduce_funcs;
  // inter
  int entry_Size;

private:
  void CurrentState(const std::string&);
  void Shift(const ACTION_STATE&, Unit*);
  int Goto(const ACTION_STATE&, Unit*);
  void* GetGrammarSymbol(const int);
  ENTRY NewEntry();
  void GenerateIntermediateCode(const std::string&);
  ENTRY TypeTransform(const ENTRY&, const Type*, const Type*);
  Type* MaxType(Type*, Type*);
  Type* MinType(Type*, Type*);
  bool CheckProduct(const int&);

  bool Reduce(const int&);
  ENTRY_TYPE ReduceOperators(Type*, Type*, const std::string);

  // Stmts -> Stmt Stmts
  Unit* Reduce_01();
  // Stmts -> Epsilon
  Unit* Reduce_02();
  // Stmt -> TYPE ID ;
  Unit* Reduce_03();
  // Stmt -> TYPE ID = Bool ;
  Unit* Reduce_04();
  // Stmt -> ID = Bool ;
  Unit* Reduce_05();
  // Stmt -> if ( Bool ) Instr Stmt
  Unit* Reduce_06();
  // Stmt -> if ( Bool ) Instr Stmt Jump else Instr Stmt
  Unit* Reduce_07();
  // Stmt -> while Instr ( Bool ) Instr Stmt
  Unit* Reduce_08();
  // Stmt -> do Stmt while ( Bool ) ;
  Unit* Reduce_09();
  // Bool -> Join || Bool
  Unit* Reduce_10();
  // Bool -> Join
  Unit* Reduce_11();
  // Join -> Equal && Join
  Unit* Reduce_12();
  // Join -> Equal
  Unit* Reduce_13();
  // Equal -> Ineq == Equal
  Unit* Reduce_14();
  // Equal -> Ineq != Equal
  Unit* Reduce_15();
  // Equal -> Ineq
  Unit* Reduce_16();
  // Ineq -> Arith < Arith
  Unit* Reduce_17();
  // Ineq -> Arith > Arith
  Unit* Reduce_18();
  // Ineq -> Arith <= Arith
  Unit* Reduce_19();
  // Ineq -> Arith >= Arith
  Unit* Reduce_20();
  // Ineq -> Arith
  Unit* Reduce_21();
  // Arith -> Arith + Term
  Unit* Reduce_22();
  // Arith -> Arith - Term
  Unit* Reduce_23();
  // Arith -> Term
  Unit* Reduce_24();
  // Term -> Term * Unary
  Unit* Reduce_25();
  // Term -> Term / Unary
  Unit* Reduce_26();
  // Term -> Unary
  Unit* Reduce_27();
  // Unary -> ! Unary
  Unit* Reduce_28();
  // Unary -> - Unary
  Unit* Reduce_29();
  // Unary -> Factor
  Unit* Reduce_30();
  // Factor -> ( Bool )
  Unit* Reduce_31();
  // Factor -> ID
  Unit* Reduce_32();
  // Factor -> INTEGER
  Unit* Reduce_33();
  // Factor -> FLOAT
  Unit* Reduce_34();
  // Factor -> true
  Unit* Reduce_35();
  // Factor -> false
  Unit* Reduce_36();
  // Instr -> Epsilon
  Unit* Reduce_37();
  // Jump -> Epsilon
  Unit* Reduce_38();

}; // class Parser

} // namespace parser

#endif
