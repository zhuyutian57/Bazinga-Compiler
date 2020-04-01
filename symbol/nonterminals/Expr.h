
#include <string>

#include "Nonterminal.h"
#include "../terminals/Type.h"

#ifndef _EXPR_H_
#define _EXPR_H_

namespace symbol {

inline namespace nonterminals {

#define ENTRY std::string

class Expr : public Nonterminal {

public:
  Expr(const ENTRY& e, Type *tp)
    : Nonterminal(Tag::EXPR), type(tp), entry(e) {}
  Expr(const ENTRY& e, Type *tp, const TAG& tag)
    : Nonterminal(tag), type(tp), entry(e) {}
  ~Expr() {}

  const ENTRY& Entry() { return entry; }

  terminals::Type *Type() { return type; }

private:
  ENTRY entry;
  terminals::Type *type;

}; // class Expr

} // namespace nonterminals

} // namespace symbol

#endif
