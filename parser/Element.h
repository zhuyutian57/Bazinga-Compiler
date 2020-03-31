
#include "Expr.h"
#include "Factor.h"
#include "Stmt.h"
#include "Stmts.h"
#include "Term.h"
#include "Unary.h"

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

namespace parser {

class Element {

public:
  Element(void *e)
    : state(-1), ele(e) {}
  Element(const int& s, void* e)
    : state(s), ele(e) {}
  ~Element() {
    if(ele != NULL) Delete();
  }

  const int& State() { return state; }
  void* Ele() { return ele; }

  void SetState(const int& s) { state = s; }
  void SetEle(void *ptr) { ele = ptr; }

private:
  int state;
  void *ele;

private:
  void Delete() {
    const int& tag = ((Unit*)ele)->Tag();
    if(tag < NONTERMINAL_BEGIN) return;
    switch(tag) {
      case Tag::STMTS : delete (Stmts*)ele; break;
      case Tag::STMT  : delete (Stmt*)ele;  break;
      case Tag::EXPR  : delete (Expr*)ele;  break;
      case Tag::TERM  : delete (Term*)ele;  break;
      case Tag::UNARY : delete (Unary*)ele; break;
      case Tag::FACTOR: delete (Factor*)ele;break;
    }
  }

}; // class Element

} // namespace parser

#endif
