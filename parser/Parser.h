
#include <functional>
#include <stack>
#include <vector>

#include "Action.h"

#include "../lexer/Lexer.h"

#ifndef _PARSER_H_
#define _PARSER_H_

namespace parser {

class Parser {

public:
  Parser() {/*{{{*/
    lok = NULL;
    lex = new lexer::Lexer();
    action = new Action();
    state_stack = new std::stack<State>;
    units_stack = new std::stack<void*>;
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
    reduce_funcs->push_back(std::bind(&reduce_18, this));
    reduce_funcs->push_back(std::bind(&reduce_19, this));
  }
  ~Parser() {
    delete lex;
    delete action;
    delete state_stack;
    delete units_stack;
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
  void* lok;
  lexer::Lexer *lex;
  Action *action;
  std::stack<State>* state_stack;
  std::stack<void*>* units_stack;
  std::vector<std::function<bool()> >* reduce_funcs;

private:
  inline void shift(/*{{{*/
      const State& state, void* input_ptr) {
    state_stack->push(state);
    units_stack->push(input_ptr);
  }/*}}}*/

  inline bool GOTO() {/*{{{*/
    return true;
  }/*}}}*/

  inline bool reduce(const int& prod_id) {/*{{{*/
    return (*reduce_funcs)[prod_id]();
  }/*}}}*/

  //TODO implement semantic actions
  //Stmts -> Stmts Stmt
  bool reduce_01() {
    
    return true;
  }

  //Stmts -> Epsilon
  bool reduce_02() {
    return true;
  }

  //Stmt -> TYPE ID ADD_ID ;
  bool reduce_03() {
    return true;
  }

  //Stmt -> TYPE ID ADD_ID = Expr ;
  bool reduce_04() {
    return true;
  }

  //Stmt -> ID ID_EXIST = Expr ;
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

  //ADD_ID -> Epsilon
  bool reduce_18() {
    return true;
  }

  //ID_EXIST -> Epsilon
  bool reduce_19() {
    return true;
  }

}; // class Parser

} // namespace parser

#endif
