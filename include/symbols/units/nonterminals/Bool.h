
#include "Expr.h"

#ifndef _BOOL_H_
#define _BOOL_H_

namespace symbols {

inline namespace nonterminals {

class Bool : public Expr {

public:
  Bool(const ENTRY&, Type*);
  ~Bool() {}

}; // class Bool

} // namespace nonterminals

} // namespace symbols

#endif
