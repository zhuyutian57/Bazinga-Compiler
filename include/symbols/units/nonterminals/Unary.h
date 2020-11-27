
#include "Expr.h"

#ifndef _UNARY_H_
#define _UNARY_H_

namespace symbols {

inline namespace nonterminals {

class Unary : public Expr {

public:
  Unary(const ENTRY&, Type*);
  ~Unary() {}

}; // class Unary

} // namespace nonterminals

} // namespace symbols

#endif
