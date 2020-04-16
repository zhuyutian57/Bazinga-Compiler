
#include "Expr.h"

#ifndef _TERM_H_
#define _TERM_H_

namespace symbols {

inline namespace nonterminals {

class Term : public Expr {

public:
  Term(const ENTRY&, terminals::Type*);
  ~Term() {}

private:

}; // class Term

} // namespace nonterminals

} // namespace symbols

#endif
