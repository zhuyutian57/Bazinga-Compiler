
#include "Expr.h"
#include "Factor.h"

#ifndef _UNARY_H_
#define _UNARY_H_

namespace parser {

class Unary : public Expr {

public:
  Unary(const ENTRY& entry, lexer::Type *type)
    : Expr(entry, type, Tag::UNARY) {}
  ~Unary() {}

private:

}; // class Unary

} // namespace Parser

#endif
