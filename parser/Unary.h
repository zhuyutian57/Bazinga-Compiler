
#include "Nonterminal.h"

#ifndef _UNARY_H_
#define _UNARY_H_

namespace parser {

class Unary : public Nonterminal {

public:
  Unary() : Nonterminal(Tag::UNARY){}
  ~Unary(){}

private:

}; // class Unary

} // namespace Parser

#endif
