
#include "Expr.h"

#ifndef _Arith_H_
#define _Arith_H_

namespace symbols {

inline namespace nonterminals {

class Arith : public Expr {

public:
  Arith(const ENTRY&, Type*);
  ~Arith() {}

}; // class Arith

} // namespace nonterminals

} // namespace symbols

#endif
