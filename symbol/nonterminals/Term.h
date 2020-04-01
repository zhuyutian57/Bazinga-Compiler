
#include "Expr.h"

#ifndef _TERM_H_
#define _TERM_H_

namespace symbol {

inline namespace nonterminals {

class Term : public Expr {

public:
  Term(const ENTRY& entry, terminals::Type *type)
    : Expr(entry, type, Tag::TERM) {}
  ~Term() {}

private:

}; // class Term

} // namespace nonterminals

} // namespace symbol

#endif
