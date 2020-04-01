
#include "Expr.h"

#ifndef _FACTOR_H_
#define _FACTOR_H_

namespace symbol {

inline namespace nonterminals {

class Factor : public Expr {

public:
  Factor(const ENTRY& entry, terminals::Type *type)
    : Expr(entry, type, Tag::FACTOR) {}
  ~Factor() {}

private:

}; // class Factor

} // namespace nonterminals

} // namespace symbol

#endif
