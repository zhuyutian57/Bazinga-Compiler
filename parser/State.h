
#include "../symbol/UnitSet.h"
using namespace symbol;

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

namespace parser {

class State {

public:
  State(void *gs)
    : state_number(-1), grammar_symbol(gs) {}
  State(const int& s, void* gs)
    : state_number(s), grammar_symbol(gs) {}
  ~State() {
    if(grammar_symbol != NULL)
      DeleteGrammarSymbol();
  }

  const int& StateNumber() { return state_number; }
  void* GrammarSymbol() { return grammar_symbol; }

private:
  int state_number;
  void *grammar_symbol;

  void DeleteGrammarSymbol() {/*{{{*/
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
  }/*}}}*/

}; // class State

} // namespace parser

#endif
