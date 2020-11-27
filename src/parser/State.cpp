
#include "State.h"

using namespace parser;

State::State(Unit* gs)
  : state_number(-1), grammar_symbol(gs) {}
State::State(const int& s, Unit* gs)
  : state_number(s), grammar_symbol(gs) {}
State::~State() {
  if(grammar_symbol != NULL)
    DeleteGrammarSymbol();
}

const int& State::StateNumber() { return state_number; }
Unit* State::GrammarSymbol() { return grammar_symbol; }

void State::DeleteGrammarSymbol() {
  if(grammar_symbol->Tag() < NONTERMINAL_BEGIN) return;
  delete grammar_symbol; 
}
