
#include "Nonterminal.h"

#ifndef _EXPR_H_
#define _EXPR_H_

namespace parser {

class Expr : public Nonterminal {

public:
  Expr(const ADDR adr)
    : Nonterminal(Tag::EXPR, adr) {}
  ~Expr(){}

private:

}; // class Expr

} // namespace Parser

#endif
