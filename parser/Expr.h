
#include <string>

#include "Nonterminal.h"

#include "../lexer/Type.h"

#ifndef _EXPR_H_
#define _EXPR_H_

namespace parser {

#define ENTRY std::string

class Expr : public Nonterminal {

public:
  Expr(const ENTRY& e, lexer::Type *tp)
    : Nonterminal(Tag::EXPR), type(tp), entry(e) {}
  Expr(const ENTRY& e, lexer::Type *tp, const TAG& tag)
    : Nonterminal(tag), type(tp), entry(e) {}
  ~Expr() {}

  const ENTRY& Entry() { return entry; }

  lexer::Type *Type() { return type; }

private:
  ENTRY entry;
  lexer::Type *type;

}; // class Expr

} // namespace Parser

#endif
