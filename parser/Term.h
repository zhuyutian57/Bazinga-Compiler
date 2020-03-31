
#include "Expr.h"
#include "Unary.h"

#ifndef _TERM_H_
#define _TERM_H_

namespace parser {

class Term : public Expr {

public:
  Term(const ENTRY& entry, lexer::Type *type)
    : Expr(entry, type, Tag::TERM) {}
  ~Term() {}

private:

}; // class Term

} // namespace Parser

#endif
