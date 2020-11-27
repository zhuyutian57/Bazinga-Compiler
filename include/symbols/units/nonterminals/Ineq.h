
#include "Expr.h"

#ifndef _INEQ_H_
#define _INEQ_H_

namespace symbols {

inline namespace nonterminals {

class Ineq : public Expr {

public:
  Ineq(const ENTRY&, Type*);
  ~Ineq() {}

}; // class Ineq

} // namespace nonterminals

} // namespace symbols

#endif
