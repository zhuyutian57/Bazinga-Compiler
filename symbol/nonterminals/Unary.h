
#include "Expr.h"

#ifndef _UNARY_H_
#define _UNARY_H_

namespace symbol {

inline namespace nonterminals {

class Unary : public Expr {

public:
  Unary(const ENTRY& entry, terminals::Type *type)
    : Expr(entry, type, Tag::UNARY) {}
  ~Unary() {}

private:

}; // class Unary

} // namespace nonterminals

} // namespace symbol

#endif
