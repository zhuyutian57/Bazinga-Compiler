
#include "Nonterminal.h"

#ifndef _FACTOR_H_
#define _FACTOR_H_

namespace parser {

class Factor : public Nonterminal {

public:
  Factor(const ADDR adr)
    : Nonterminal(Tag::FACTOR, adr){}
  ~Factor(){}

private:

}; // class Factor

} // namespace Parser

#endif
