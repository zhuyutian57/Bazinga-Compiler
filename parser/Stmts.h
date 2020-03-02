
#include "Nonterminal.h"

#ifndef _STMTS_H_
#define _STMTS_H_

namespace parser {

class Stmts : public Nonterminal {

public:
  Stmts() : Nonterminal(Tag::STMTS) {}
  ~Stmts(){}

private:

}; // class Stmts

} // namespace Parser

#endif
