
#include "Nonterminal.h"
#include "Type.h"

#ifndef _EXPR_H_
#define _EXPR_H_

namespace symbols {

inline namespace nonterminals {

#define ENTRY std::string

class Expr : public Nonterminal {

public:
  Expr(const ENTRY&, terminals::Type*);
  Expr(const ENTRY&, terminals::Type*, const TAG&);
  ~Expr() {}

  const ENTRY& Entry();
  terminals::Type* Type();

private:
  ENTRY entry;
  terminals::Type *type;

}; // class Expr

} // namespace nonterminals

} // namespace symbols

#endif
