
#include "UnitSet.h"

using namespace symbols;

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

namespace parser {

class State {

public:
  State(Unit*);
  State(const int&, Unit*);
  ~State();

  const int& StateNumber();
  Unit* GrammarSymbol();

private:
  int state_number;
  Unit* grammar_symbol;

private:
  void DeleteGrammarSymbol();

}; // class State

} // namespace parser

#endif
