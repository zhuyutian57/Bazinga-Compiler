
#include <stack>

#include "Action.h"

#ifndef _PARSER_H_
#define _PARSER_H_

namespace parser {

class Parser {

public:
  Parser() {
    action = new Action();
    state_stack = new std::stack<State>;
    units_stack = new std::stack<void*>;
  }
  ~Parser() {
    delete action;
    delete state_stack;
    delete units_stack;
  }

  bool Build(const char* grammars) {
    if(!action->Build(grammars)) return false;
    return true;
  }

private:
  Action *action;
  std::stack<State>* state_stack;
  std::stack<void*>* units_stack;

private:
  void shift() {}
  bool reduce() {}

}; // class Parser

} // namespace parser

#endif
