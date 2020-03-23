
#include <string>

#include "../symbol/Tag.h"
#include "../symbol/Unit.h"
using namespace symbol;

#ifndef _NONTERMINAL_H_
#define _NONTERMINAL_H_

namespace parser {

#define ADDR std::string

class Nonterminal : public Unit {

public:
  Nonterminal(const int t)
    : Unit(t) {}
  Nonterminal(const int t, const ADDR adr)
    : Unit(t), addr(adr) {}
  ~Nonterminal(){}

private:
  ADDR addr;

}; // class Nonterminal

} // namespace parser

#endif
