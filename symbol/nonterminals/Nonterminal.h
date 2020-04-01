
#include <string>

#include "../Tag.h"
#include "../Unit.h"

#ifndef _NONTERMINAL_H_
#define _NONTERMINAL_H_

namespace symbol {

inline namespace nonterminals {

class Nonterminal : public Unit {

public:
  Nonterminal(const int t)
    : Unit(t) {}
  ~Nonterminal() {}

private:

}; // class Nonterminal

} // namespace nonterminals

} // namespace symbol

#endif
