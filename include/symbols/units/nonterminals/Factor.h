
#include "Expr.h"

#ifndef _FACTOR_H_
#define _FACTOR_H_

namespace symbols {

inline namespace nonterminals {

class Factor : public Expr {

public:
  Factor(const ENTRY&, Type*);
  ~Factor() {}

}; // class Factor

} // namespace nonterminals

} // namespace symbols

#endif
