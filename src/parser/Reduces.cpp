
#include "Parser.h"
using namespace parser;

bool Parser::Reduce(const int& product_index) {
  if(!CheckProduct(product_index)) return false;
  void* n_unit = reduce_funcs[product_index]();
  if(n_unit == NULL) return false;
  int n_state = Goto(e_stack.Top()->StateNumber(), (Unit*)n_unit);
  STACK_PUSH(n_state, n_unit);
  return true;
}

// Stmts -> Stmt Stmts
void* Parser::Reduce_01() {
  Stmts *n_stmts = new Stmts();
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  STACK_POP(2);
  return n_stmts;
}

// Stmts -> Epsilon
void* Parser::Reduce_02() {
  Stmts *n_stmts = new Stmts();
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  return n_stmts;
}

// Stmt -> TYPE ID ;
void* Parser::Reduce_03() {
  Type *type = (Type*)GetGrammarSymbol(-3);
  Terminal *word = (Terminal*)GetGrammarSymbol(-2);
  /*------------Semantic Action------------*/
  if(env->InScope(word)) {
    Error(word->Lexeme() + " is defined!\n");
    return NULL;
  }
  env->Put(word, type);
  /*---------------------------------------*/
  Stmt *n_stmt = new Stmt();
  STACK_POP(3);
  return n_stmt;
}

// Stmt -> TYPE ID = Expr ;
void* Parser::Reduce_04() {
  Type *type = (Type*)GetGrammarSymbol(-5);
  Terminal *word = (Terminal*)GetGrammarSymbol(-4);
  Expr *expr = (Expr*)GetGrammarSymbol(-2);
  /*------------Semantic Action------------*/
  if(env->InScope(word)) {
    Error(word->Lexeme() + " has been defined!\n");
    return NULL;
  }
  env->Put(word, type);
  ENTRY n_entry;
  if(expr->Type() != type) {
    n_entry = TypeTransform(expr->Entry(), expr->Type(), type);
  } else {
    n_entry = expr->Entry();
  }
  GenerateIntermediateCode(word->Lexeme() + " = " + n_entry);
  /*---------------------------------------*/
  Stmt *n_stmt = new Stmt();
  STACK_POP(5);
  return n_stmt;
}

// Stmt -> ID = Expr ;
void* Parser::Reduce_05() {
  Terminal *word = (Terminal*)GetGrammarSymbol(-4);
  Expr *expr = (Expr*)GetGrammarSymbol(-2);
  /*------------Semantic Action------------*/
  Id *id = env->GetId(word->Lexeme());
  if(id == NULL) {
    Error(word->Lexeme() + " is not defined!");
    return NULL;
  }
  ENTRY n_entry;
  if(expr->Type() != id->Type()) {
    n_entry = TypeTransform(expr->Entry(),
        expr->Type(), id->Type());
  } else {
    n_entry = expr->Entry();
  }
  GenerateIntermediateCode(id->Name() + " = " + n_entry);
  /*---------------------------------------*/
  Stmt *n_stmt = new Stmt();
  STACK_POP(4);
  return n_stmt;
}

// The semantic actions of + - * / are same.
ENTRY_TYPE Parser::ReduceExpression(
    auto *expr_1, auto *expr_2, const std::string op) {
  /*------------Semantic Action------------*/
  ENTRY n_entry, max_entry, min_entry;
  Type *max_type = MaxType(expr_1->Type(), expr_2->Type());  
  if(expr_1->Type() != max_type) {
    min_entry = TypeTransform(expr_1->Entry(), expr_1->Type(), max_type);
    max_entry = expr_2->Entry();
  } else if(expr_2->Type() != max_type) {
    min_entry = TypeTransform(expr_2->Entry(), expr_2->Type(), max_type);
    max_entry = expr_1->Entry();
  } else {
    min_entry = expr_2->Entry();
    max_entry = expr_1->Entry();
  }
  n_entry = NewEntry();
  GenerateIntermediateCode(n_entry + " = " + max_entry + " + "+ min_entry);
  /*---------------------------------------*/
  return std::make_pair(n_entry, max_type);
}

// Expr -> Expr + Term
void* Parser::Reduce_06() {
  Expr *expr = (Expr*)GetGrammarSymbol(-3);
  Term *term = (Term*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  ENTRY_TYPE et = Parser::ReduceExpression(expr, term, " + ");
  /*---------------------------------------*/
  Expr *n_expr = new Expr(et.first, et.second);
  STACK_POP(3);
  return n_expr;
}

// Expr -> Expr - Term
void* Parser::Reduce_07() {
  Expr *expr = (Expr*)GetGrammarSymbol(-3);
  Term *term = (Term*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  ENTRY_TYPE et = Parser::ReduceExpression(expr, term, " - ");
  /*---------------------------------------*/
  Expr *n_expr = new Expr(et.first, et.second);
  STACK_POP(3);
  return n_expr;
}

// Expr -> Term
void* Parser::Reduce_08() {
  Term *term = (Term*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Expr *n_expr = new Expr(term->Entry(), term->Type());
  STACK_POP(1);
  return n_expr;
}

// Term -> Term * Unary
void* Parser::Reduce_09() {
  Term *term = (Term*)GetGrammarSymbol(-3);
  Unary *unary = (Unary*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  ENTRY_TYPE et = Parser::ReduceExpression(term, unary, " * ");
  /*---------------------------------------*/
  Term *n_term = new Term(et.first, et.second);
  STACK_POP(3);
  return n_term;
}

// Term -> Term / Unary
void* Parser::Reduce_10() {
  Term *term = (Term*)GetGrammarSymbol(-3);
  Unary *unary = (Unary*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  ENTRY_TYPE et = Parser::ReduceExpression(term, unary, " / ");
  /*---------------------------------------*/
  Term *n_term = new Term(et.first, et.second);
  STACK_POP(3);
  return n_term;
}

// Term -> Unary
void* Parser::Reduce_11() {
  Unary *unary = (Unary*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Term *n_term = new Term(unary->Entry(), unary->Type());
  STACK_POP(1);
  return n_term;
}

// Unary -> - Unary
void* Parser::Reduce_12() {
  Unary *unary = (Unary*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  ENTRY n_entry = NewEntry();
  GenerateIntermediateCode(n_entry + " = " + " minus " + unary->Entry());
  /*---------------------------------------*/
  Unary *n_unary = new Unary(n_entry, unary->Type());
  STACK_POP(2);
  return n_unary;
}

// Unary -> Factor
void* Parser::Reduce_13() {
  Factor *factor = (Factor*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Unary *n_unary =
    new Unary(factor->Entry(), factor->Type());
  STACK_POP(1);
  return n_unary;
}

// Factor -> ( Expr )
void* Parser::Reduce_14() {
  Expr *expr = (Expr*)GetGrammarSymbol(-2);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Factor *n_factor =
    new Factor(expr->Entry(), expr->Type());
  STACK_POP(3);
  return n_factor;
}

// Factor -> ID
void* Parser::Reduce_15() {
  Terminal *word = (Terminal*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  Id *id = env->GetId(word->Lexeme());
  if(id == NULL) {
    Error(word->Lexeme() + " is not defined!");
    return NULL;
  }
  /*---------------------------------------*/
  Factor *n_factor =
    new Factor(id->Name(), id->Type());
  STACK_POP(1);
  return n_factor;
}

// Factor -> INTEGER
void* Parser::Reduce_16() {
  Integer *_int = (Integer*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Factor *n_factor =
    new Factor(_int->Lexeme(), env->GetType("int"));
  STACK_POP(1);
  return n_factor;
}

// Factor -> FLOAT
void* Parser::Reduce_17() {
  Real *_float = (Real*)GetGrammarSymbol(-1);
  /*------------Semantic Action------------*/
  /*---------------------------------------*/
  Factor *n_factor =
    new Factor(_float->Lexeme(), env->GetType("float"));
  STACK_POP(1);
  return n_factor;
}
