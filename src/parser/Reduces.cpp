
#include "Parser.h"
using namespace parser;

bool Parser::Reduce(const int& product_index) {
  if(!CheckProduct(product_index)) return false;
  Unit* n_unit = reduce_funcs[product_index]();
  if(n_unit == NULL) return false;
  int n_state = Goto(e_stack.Top()->StateNumber(), (Unit*)n_unit);
  STACK_PUSH(n_state, n_unit);
  return true;
}

ENTRY_TYPE ReduceOperators(Type*, Type*, const std::string) {}

// Stmts -> Stmt Stmts
Unit* Parser::Reduce_01() {}
// Stmts -> Epsilon
Unit* Parser::Reduce_02() {}
// Stmt -> TYPE ID ;
Unit* Parser::Reduce_03() {}
// Stmt -> TYPE ID = Bool ;
Unit* Parser::Reduce_04() {}
// Stmt -> ID = Bool ;
Unit* Parser::Reduce_05() {}
// Stmt -> if ( Bool ) Line Stmt
Unit* Parser::Reduce_06() {}
// Stmt -> if ( Bool ) Line Stmt Jump else Line Stmt
Unit* Parser::Reduce_07() {}
// Stmt -> while Line ( Bool ) Line Stmt
Unit* Parser::Reduce_08() {}
// Stmt -> do Stmt while ( Bool ) ;
Unit* Parser::Reduce_09() {}
// Bool -> Join || Bool
Unit* Parser::Reduce_10() {}
// Bool -> Join
Unit* Parser::Reduce_11() {}
// Join -> Equal && Join
Unit* Parser::Reduce_12() {}
// Join -> Equal
Unit* Parser::Reduce_13() {}
// Equal -> Ineq == Equal
Unit* Parser::Reduce_14() {}
// Equal -> Ineq != Equal
Unit* Parser::Reduce_15() {}
// Equal -> Ineq
Unit* Parser::Reduce_16() {}
// Ineq -> Arith < Arith
Unit* Parser::Reduce_17() {}
// Ineq -> Arith > Arith
Unit* Parser::Reduce_18() {}
// Ineq -> Arith <= Arith
Unit* Parser::Reduce_19() {}
// Ineq -> Arith >= Arith
Unit* Parser::Reduce_20() {}
// Ineq -> Arith
Unit* Parser::Reduce_21() {}
// Arith -> Arith + Term
Unit* Parser::Reduce_22() {}
// Arith -> Arith - Term
Unit* Parser::Reduce_23() {}
// Arith -> Term
Unit* Parser::Reduce_24() {}
// Term -> Term * Unary
Unit* Parser::Reduce_25() {}
// Term -> Term / Unary
Unit* Parser::Reduce_26() {}
// Term -> Unary
Unit* Parser::Reduce_27() {}
// Unary -> ! Unary
Unit* Parser::Reduce_28() {}
// Unary -> - Unary
Unit* Parser::Reduce_29() {}
// Unary -> Factor
Unit* Parser::Reduce_30() {}
// Factor -> ( Bool )
Unit* Parser::Reduce_31() {}
// Factor -> ID
Unit* Parser::Reduce_32() {}
// Factor -> INTEGER
Unit* Parser::Reduce_33() {}
// Factor -> FLOAT
Unit* Parser::Reduce_34() {}
// Factor -> true
Unit* Parser::Reduce_35() {}
// Factor -> false
Unit* Parser::Reduce_36() {}
// Line -> Epsilon
Unit* Parser::Reduce_37() {}
// Jump -> Epsilon
Unit* Parser::Reduce_38() {}
