
#include "Expr.h"

#ifndef _EQUAL_H_
#define _EQUAL_H_

namespace symbols {

inline namespace nonterminals {

class Equal : public Expr {

public:
  Equal(const ENTRY&, Type*);
  ~Equal() {}

}; // class Equal

} // namespace nonterminals

} // namespace symbols

#endif
