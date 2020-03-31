
#include "Expr.h"

#ifndef _FACTOR_H_
#define _FACTOR_H_

namespace parser {

class Factor : public Expr {

public:
  Factor(const ENTRY& entry, lexer::Type *type)
    : Expr(entry, type, Tag::FACTOR) {}
  ~Factor() {}

private:

}; // class Factor

} // namespace Parser

#endif
