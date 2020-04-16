
#include "UnitSet.h"

using namespace symbols;

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

namespace parser {

class State {

public:
  State(void*);
  State(const int&, void*);
  ~State();

  const int& StateNumber();
  void* GrammarSymbol();

private:
  int state_number;
  void *grammar_symbol;

private:
  void DeleteGrammarSymbol();

}; // class State

} // namespace parser

#endif
