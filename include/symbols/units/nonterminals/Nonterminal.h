
#include "Stl.h"
#include "Tag.h"
#include "Unit.h"

#ifndef _NONTERMINAL_H_
#define _NONTERMINAL_H_

namespace symbols {

inline namespace nonterminals {

class Nonterminal : public Unit {

public:
  Nonterminal(const int t);
  ~Nonterminal() {}

private:

}; // class Nonterminal

} // namespace nonterminals

} // namespace symbols

#endif
