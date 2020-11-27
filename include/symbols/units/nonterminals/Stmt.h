
#include "Stmts.h"

#ifndef _STMT_H_
#define _STMT_H_

namespace symbols {

inline namespace nonterminals {

class Stmt : public Stmts {

public:
  Stmt();
  ~Stmt();

  void AddInstr(INSTRLIST*);
  INSTRLIST* NextList();

private:
  INSTRLIST* nextlist;

}; // class Stmt

} // namespace nonterminals

} // namespace symbols

#endif
