
#include "Nonterminal.h"

#ifndef _TERM_H_
#define _TERM_H_

namespace parser {

class Term : public Nonterminal {

public:
  Term() : Nonterminal(Tag::TERM){}
  ~Term(){}

private:

}; // class Term

} // namespace Parser

#endif
