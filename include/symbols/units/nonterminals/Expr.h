
#include "Type.h"
#include "Unit.h"

#ifndef _EXPR_H_
#define _EXPR_H_

namespace symbols {

inline namespace nonterminals {

class Expr : public Unit {

public:
  Expr(const ENTRY&, Type*, const TAG&);
  ~Expr();

  const ENTRY& Entry();
  Type* GetType();
  std::set<int>* TrueList();
  std::set<int>* FalseList();
  void AddLine(const int, bool);

private:
  ENTRY entry;
  Type* type;
  std::set<int>* truelist;
  std::set<int>* falselist;

}; // class Expr

} // namespace nonterminals

} // namespace symbols

#endif
