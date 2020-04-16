
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
  Terminal *lok;
  lexer::Lexer *lex;
  // parser
  Action *action_table;
  Stack<State*> e_stack;
  std::vector<std::function<void*()> > reduce_funcs;
  // inter
  int entry_Size;

private:
  void CurrentState(const std::string&);
  void Shift(const ACTION_STATE&, void*);
  int Goto(const ACTION_STATE&, Unit*);
  void* GetGrammarSymbol(const int);
  ENTRY NewEntry();
  void GenerateIntermediateCode(const std::string&);
  ENTRY TypeTransform(const ENTRY&, const Type*, const Type*);
  Type* MaxType(Type*, Type*);
  Type* min_type(Type*, Type*);
  bool CheckProduct(const int&);

  bool Reduce(const int&);
  ENTRY_TYPE ReduceExpression(auto*, auto*, const std::string);

  // Stmts -> Stmt Stmts
  void* Reduce_01();
  // Stmts -> Epsilon
  void* Reduce_02();
  // Stmt -> TYPE ID ;
  void* Reduce_03();
  // Stmt -> TYPE ID = Expr ;
  void* Reduce_04();
  // Stmt -> ID = Expr ;
  void* Reduce_05();
  // Expr -> Expr + Term
  void* Reduce_06();
  // Expr -> Expr - Term
  void* Reduce_07();
  // Expr -> Term
  void* Reduce_08();
  // Term -> Term * Unary
  void* Reduce_09();
  // Term -> Term / Unary
  void* Reduce_10();
  // Term -> Unary
  void* Reduce_11();
  // Unary -> - Unary
  void* Reduce_12();
  // Unary -> Factor
  void* Reduce_13();
  // Factor -> ( Expr )
  void* Reduce_14();
  // Factor -> ID
  void* Reduce_15();
  // Factor -> INTEGER
  void* Reduce_16();
  // Factor -> FLOAT
  void* Reduce_17();

}; // class Parser

} // namespace parser

#endif
