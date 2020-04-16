
#include "State.h"

using namespace parser;

State::State(void *gs)
  : state_number(-1), grammar_symbol(gs) {}
State::State(const int& s, void* gs)
  : state_number(s), grammar_symbol(gs) {}
State::~State() {
  if(grammar_symbol != NULL)
    DeleteGrammarSymbol();
}

const int& State::StateNumber() { return state_number; }
void* State::GrammarSymbol() { return grammar_symbol; }

void State::DeleteGrammarSymbol() {
  const int& tag = ((Unit*)grammar_symbol)->Tag();
  if(tag < NONTERMINAL_BEGIN) return;
  switch(tag) {
    case Tag::STMTS : delete (Stmts*)grammar_symbol;  break;
    case Tag::STMT  : delete (Stmt*)grammar_symbol;   break;
    case Tag::EXPR  : delete (Expr*)grammar_symbol;   break;
    case Tag::TERM  : delete (Term*)grammar_symbol;   break;
    case Tag::UNARY : delete (Unary*)grammar_symbol;  break;
    case Tag::FACTOR: delete (Factor*)grammar_symbol; break;
  }
}
