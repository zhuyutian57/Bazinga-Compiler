
#include "Nonterminal.h"

#ifndef _STMT_H_
#define _STMT_H_

namespace parser {

class Stmt : public Nonterminal {

public:
  Stmt() : Nonterminal(Tag::STMT) {}
  ~Stmt() {}

private:

}; // class Stmt

} // namespace Parser

#endif
