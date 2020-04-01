
#include "Nonterminal.h"

#ifndef _STMTS_H_
#define _STMTS_H_

namespace symbol {

inline namespace nonterminals {

class Stmts : public Nonterminal {

public:
  Stmts() : Nonterminal(Tag::STMTS) {}
  ~Stmts() {}

private:

}; // class Stmts

} // namespace nonterminals

} // namespace symbol

#endif
