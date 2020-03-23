
#include <functional>
#include <stack>
#include <string>
#include <vector>

#include "Action.h"
#include "Element.h"

#include "../bin/Stack.h"
#include "../lexer/Lexer.h"
#include "../symbol/Env.h"
using namespace lexer;
using namespace symbol;

#ifndef _PARSER_H_
#define _PARSER_H_

namespace parser {

#define STACK_POP(states_size) \
  for(int i = 0; i < states_size; i++) { \
    e_stack->pop(); \
  }

class Parser {

public:
  Parser() : env(NULL), lok(NULL){/*{{{*/
    lex = new lexer::Lexer();
    action = new Action();
    e_stack = new bin::Stack<Element>;
    reduce_funcs = new std::vector<std::function<bool()> >;
    reduce_funcs->push_back(NULL); // Accepted
    reduce_funcs->push_back(std::bind(&reduce_01, this));
    reduce_funcs->push_back(std::bind(&reduce_02, this));
    reduce_funcs->push_back(std::bind(&reduce_03, this));
    reduce_funcs->push_back(std::bind(&reduce_04, this));
    reduce_funcs->push_back(std::bind(&reduce_05, this));
    reduce_funcs->push_back(std::bind(&reduce_06, this));
    reduce_funcs->push_back(std::bind(&reduce_07, this));
    reduce_funcs->push_back(std::bind(&reduce_08, this));
    reduce_funcs->push_back(std::bind(&reduce_09, this));
    reduce_funcs->push_back(std::bind(&reduce_10, this));
    reduce_funcs->push_back(std::bind(&reduce_11, this));
    reduce_funcs->push_back(std::bind(&reduce_12, this));
    reduce_funcs->push_back(std::bind(&reduce_13, this));
    reduce_funcs->push_back(std::bind(&reduce_14, this));
    reduce_funcs->push_back(std::bind(&reduce_15, this));
    reduce_funcs->push_back(std::bind(&reduce_16, this));
    reduce_funcs->push_back(std::bind(&reduce_17, this));
  }
  ~Parser() {
    delete lex;
    delete action;
    delete e_stack;
    delete reduce_funcs;
  }/*}}}*/

  bool Build(const char* regular_definations, /*{{{*/
      const char* grammars) {
    if(!lex->Build(regular_definations)) return false;
    if(!action->Build(grammars)) return false;
    return true;
  }/*}}}*/

  bool Run() { return true; }

private:
  Env *env;
  void* lok;
  lexer::Lexer *lex;
  Action *action;
  bin::Stack<Element>* e_stack;
  std::vector<std::function<bool()> >* reduce_funcs;

private:
  inline void shift(/*{{{*/
      const STATE& state, void* input_ptr) {
    e_stack->push(Element(state, input_ptr));
  }/*}}}*/

  inline bool GOTO(const STATE& s, Unit* unit) {/*{{{*/
    const std::string& ac = action->ACTION(s, unit->Tag());
    if(ac == ACTION_ERROR) return false;
    e_stack->top().Set_state(std::stoi(ac));
    return true;
  }/*}}}*/

  inline bool reduce(const int& prod_id) {/*{{{*/
    if(!(*reduce_funcs)[prod_id]())
      return false;
    return GOTO(e_stack->top().State(),
        (Unit*)e_stack->top().Ele());
  }/*}}}*/

  //TODO implement semantic actions
  //Stmts -> Stmt Stmts
  bool reduce_01() {
    Stmts *stmts = new Stmts();
    STACK_POP(1);
    e_stack->top().Set_ele(stmts);
    return true;
  }

  //Stmts -> Epsilon
  bool reduce_02() {
    Stmts *stmts = new Stmts();
    e_stack->push(Elestmts);
    return true;
  }

  //Stmt -> TYPE ID ;
  bool reduce_03() {
    Stmt *stmt = new Stmt();
    //TODO semantic action
    STACK_POP(2);
    e_stack->top().Set_ele(stmt);
    return true;
  }

  //Stmt -> TYPE ID = Expr ;
  bool reduce_04() {
    Stmt *stmt = new Stmt();
    //TODO semantic action
    STACK_POP(4);
    e_stack->top().Set_ele(stmt);
    return true;
  }

  //Stmt -> ID = Expr ;
  bool reduce_05() {
    return true;
  }

  //Expr -> Expr + Term
  bool reduce_06() {
    return true;
  }

  //Expr -> Expr - Term
  bool reduce_07() {
    return true;
  }

  //Expr -> Term
  bool reduce_08() {
    return true;
  }

  //Term -> Term * Unary
  bool reduce_09() {
    return true;
  }

  //Term -> Term / Unary
  bool reduce_10() {
    return true;
  }

  //Term -> Unary
  bool reduce_11() {
    return true;
  }

  //Unary -> - Unary
  bool reduce_12() {
    return true;
  }

  //Unary -> Factor
  bool reduce_13() {
    return true;
  }

  //Factor -> ( Expr )
  bool reduce_14() {
    return true;
  }

  //Factor -> ID
  bool reduce_15() {
    return true;
  }

  //Factor -> INTEGER
  bool reduce_16() {
    return true;
  }

  //Factor -> FLOAT
  bool reduce_17() {
    return true;
  }

}; // class Parser

} // namespace parser

#endif
