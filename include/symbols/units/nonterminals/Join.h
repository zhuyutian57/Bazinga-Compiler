
#include "Expr.h"

#ifndef _JOIN_H_
#define _JOIN_H_

namespace symbols {

inline namespace nonterminals {

class Join : public Expr {

public:
  Join(const ENTRY&, Type*);
  ~Join() {}

}; // class Join

} // namespace nonterminals

} // namespace symbols

#endif
