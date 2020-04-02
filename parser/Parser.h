
#include "Action.h"
#include "State.h"

#include "../bin/Bin.h"
#include "../lexer/Lexer.h"
#include "../symbol/Env.h"
#include "../symbol/Id.h"
#include "../symbol/UnitSet.h"
using namespace lexer;
using namespace symbol;

#ifndef _PARSER_H_
#define _PARSER_H_

namespace parser {

class Parser {

public:
  Parser() : lok(NULL), entry_Size(0) {/*{{{*/
    env = new Env();
    lex = new Lexer();
    action_table = new Action();
    reduce_funcs.push_back(NULL); // Accepted
    reduce_funcs.push_back(std::bind(&Reduce_01, this));
    reduce_funcs.push_back(std::bind(&Reduce_02, this));
    reduce_funcs.push_back(std::bind(&Reduce_03, this));
    reduce_funcs.push_back(std::bind(&Reduce_04, this));
    reduce_funcs.push_back(std::bind(&Reduce_05, this));
    reduce_funcs.push_back(std::bind(&Reduce_06, this));
    reduce_funcs.push_back(std::bind(&Reduce_07, this));
    reduce_funcs.push_back(std::bind(&Reduce_08, this));
    reduce_funcs.push_back(std::bind(&Reduce_09, this));
    reduce_funcs.push_back(std::bind(&Reduce_10, this));
    reduce_funcs.push_back(std::bind(&Reduce_11, this));
    reduce_funcs.push_back(std::bind(&Reduce_12, this));
    reduce_funcs.push_back(std::bind(&Reduce_13, this));
    reduce_funcs.push_back(std::bind(&Reduce_14, this));
    reduce_funcs.push_back(std::bind(&Reduce_15, this));
    reduce_funcs.push_back(std::bind(&Reduce_16, this));
    reduce_funcs.push_back(std::bind(&Reduce_17, this));
  }
  ~Parser() {
    delete env;
    delete lex;
    delete action_table;
  }/*}}}*/

  bool Build(const char* regular_definations, /*{{{*/
      const char* grammars) {
    if(!lex->Build(regular_definations)) return false;
    if(!action_table->Build(grammars)) return false;
    return true;
  }/*}}}*/

  bool Analyze(const char* source_code) {/*{{{*/
    if(!lex->Analyze(source_code)) return false; 
    e_stack.Push(new State(0, KeyWords::End));
    lok = lex->NextTerminal();
    while(true) {
      const ACTION_STATE& s = e_stack.Top()->StateNumber();
      const int& t = lok->Tag();
      const std::string& action = action_table->ACTION(s, t);
      CurrentState(action);
      if(action[0] == 'S') {
        const int n_state =
          std::stoi(action.substr(1, action.size()));
        e_stack.Push(new State(n_state, lok));
        lok = lex->NextTerminal();
      } else if(action[0] == 'R') {
        const int product_index =
          std::stoi(action.substr(1, action.size())); 
        if(!Reduce(product_index)) {
          bin::Error("fuck");
          return false;
        }
      } else if(action == ACCEPTED) {
        Print("ACCEPTED! NO ERROE! CONGRATULATIONS!"); 
        break;
      } else {
        Error("what's this?");
        return false;
      }
    }
    return true;
  }/*}}}*/

private:
  // symbol
  Env *env;
  // lexer
  Terminal *lok;
  lexer::Lexer *lex;
  // parser
  Action *action_table;
  Stack<State*> e_stack;
  std::vector<std::function<void*()> > reduce_funcs;
  // inter
  int entry_Size;

private:
  void CurrentState(const std::string& ac) {/*{{{*/
    int left = 48;
    for(int i = e_stack.Size(); i; i--) {
      int s = e_stack[-i]->StateNumber();
      std::cout << s << ' ';
      left -= 1 + std::to_string(s).size();
    }
    for(int i = 0; i < left; i++) std::cout << ' ';
    left = 72;
    std::cout << action_table->Units()[((Unit*)lok)->Tag()] << '\t';
    left -= 1 + action_table->Units()[((Unit*)lok)->Tag()].size();
    for(int i = 1; i <= e_stack.Size(); i++) {
      Unit *uptr = (Unit*)GetGrammarSymbol(-i);
      left -= action_table->Units()[uptr->Tag()].size() + 1;
      std::cout << action_table->Units()[uptr->Tag()] << ' ';
    }
    for(int i = 0; i < left; i++) std::cout << ' ';
    std::cout << ac << '\n';
  }/*}}}*/

  inline void Shift(/*{{{*/
      const ACTION_STATE& state, void* input_ptr) {
    e_stack.Push(new State(state, input_ptr));
  }/*}}}*/

  inline int Goto(const ACTION_STATE& s, Unit* unit) {/*{{{*/
    const std::string& ac = action_table->ACTION(s, unit->Tag());
    if(ac == ACTION_ERROR) return -1;
    return std::stoi(ac);
  }/*}}}*/

  inline void* GetGrammarSymbol(const int index) {/*{{{*/
    return e_stack[index]->GrammarSymbol();
  }/*}}}*/

  inline ENTRY new_entry() {/*{{{*/
    return std::string("t")
      + std::to_string(++entry_Size);
  }/*}}}*/

  inline void gen_inter(const std::string& inter_code) {/*{{{*/
    Print(inter_code);
  }/*}}}*/

  inline ENTRY TypeTransfrom(/*{{{*/
      const ENTRY& entry,
      const Type *type_1,
      const Type *type_2) {
    ENTRY n_entry = new_entry();
    gen_inter(n_entry + " = " + type_1->Lexeme()
        + "to" + type_2->Lexeme() + " " + entry);
    return entry;
  }/*}}}*/

  inline Type* MaxType(Type* type_1,Type* type_2) {/*{{{*/
    if(type_1->Tag() > type_2->Tag())
      return type_1;
    return type_2;
  }
  inline Type* min_type(Type* type_1,Type* type_2) {
    if(type_1->Tag() < type_2->Tag())
      return type_1;
    return type_2;
  }/*}}}*/

  bool CheckProduct(const int& product_index) {/*{{{*/
    Product* const product = action_table->GetProduct(product_index);
    if(product->Body(0) == Tag::EPSILON) return true;
    const int n = product->BodySize();
    for(int i = 0; i < n; i++) {
      const TAG b = product->Body(i);
      const TAG t = ((Unit*)GetGrammarSymbol(i - n))->Tag();
      if(b != t) return false;
    }
    return true;
  }/*}}}*/

  bool Reduce(const int& product_index) {/*{{{*/
    if(!CheckProduct(product_index)) return false;
    void* n_unit = reduce_funcs[product_index]();
    if(n_unit == NULL) return false;
    int n_state = Goto(e_stack.Top()->StateNumber(), (Unit*)n_unit);
    STACK_PUSH(n_state, n_unit);
    return true;
  }/*}}}*/

  // Stmts -> Stmt Stmts
  void* Reduce_01() {/*{{{*/
    Stmts *n_stmts = new Stmts();
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    STACK_POP(2);
    return n_stmts;
  }/*}}}*/

  // Stmts -> Epsilon
  void* Reduce_02() {/*{{{*/
    Stmts *n_stmts = new Stmts();
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    return n_stmts;
  }/*}}}*/

  // Stmt -> TYPE ID ;
  void* Reduce_03() {/*{{{*/
    Type *type = (Type*)GetGrammarSymbol(-3);
    Terminal *word = (Terminal*)GetGrammarSymbol(-2);
    /*------------Semantic Action------------*/
    if(env->InScope(word)) {
      bin::Error(word->Lexeme() + " is defined!\n");
      return NULL;
    }
    env->Put(word, type);
    /*---------------------------------------*/
    Stmt *n_stmt = new Stmt();
    STACK_POP(3);
    return n_stmt;
  }/*}}}*/

  // Stmt -> TYPE ID = Expr ;
  void* Reduce_04() {/*{{{*/
    Type *type = (Type*)GetGrammarSymbol(-5);
    Terminal *word = (Terminal*)GetGrammarSymbol(-4);
    Expr *expr = (Expr*)GetGrammarSymbol(-2);
    /*------------Semantic Action------------*/
    if(env->InScope(word)) {
      bin::Error(word->Lexeme() + " has been defined!\n");
      return NULL;
    }
    env->Put(word, type);
    ENTRY n_entry;
    if(expr->Type() != type) {
      n_entry = TypeTransfrom(expr->Entry(), expr->Type(), type);
    } else {
      n_entry = expr->Entry();
    }
    gen_inter(word->Lexeme() + " = " + n_entry);
    /*---------------------------------------*/
    Stmt *n_stmt = new Stmt();
    STACK_POP(5);
    return n_stmt;
  }/*}}}*/

  // Stmt -> ID = Expr ;
  void* Reduce_05() {/*{{{*/
    Terminal *word = (Terminal*)GetGrammarSymbol(-4);
    Expr *expr = (Expr*)GetGrammarSymbol(-2);
    /*------------Semantic Action------------*/
    Id *id = env->GetId(word->Lexeme());
    if(id == NULL) {
      bin::Error(word->Lexeme() + " is not defined!");
      return NULL;
    }
    ENTRY n_entry;
    if(expr->Type() != id->Type()) {
      n_entry = TypeTransfrom(expr->Entry(),
          expr->Type(), id->Type());
    } else {
      n_entry = expr->Entry();
    }
    gen_inter(id->Name() + " = " + n_entry);
    /*---------------------------------------*/
    Stmt *n_stmt = new Stmt();
    STACK_POP(4);
    return n_stmt;
  }/*}}}*/

  ENTRY_TYPE ReduceExpression(/*{{{*/
      auto *expr_1, auto *expr_2,
      const std::string op) {
    /*------------Semantic Action------------*/
    ENTRY n_entry;
    Type *mx_type = MaxType(expr_1->Type(), expr_2->Type());  
    if(expr_1->Type() != expr_2->Type()) {
      Expr *mi_expr;
      ENTRY tmp;
      if(expr_1->Type() != mx_type) {
        tmp = TypeTransfrom(expr_1->Entry(), expr_1->Type(), mx_type);
        mi_expr = expr_1;
      } else {
        tmp = TypeTransfrom(expr_2->Entry(), expr_2->Type(), mx_type);
        mi_expr = expr_2;
      }
      n_entry = new_entry();
      gen_inter(n_entry + " = " + mi_expr->Entry() + op + tmp);
    } else {
      n_entry = new_entry();
      gen_inter(n_entry + " = " + expr_1->Entry() + op + expr_2->Entry());
    }
    /*---------------------------------------*/
    return std::make_pair(n_entry, mx_type);
  }/*}}}*/
  
  // Expr -> Expr + Term
  void* Reduce_06() {/*{{{*/
    Expr *expr = (Expr*)GetGrammarSymbol(-3);
    Term *term = (Term*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    ENTRY_TYPE et = ReduceExpression(expr, term, " + ");
    /*---------------------------------------*/
    Expr *n_expr = new Expr(et.first, et.second);
    STACK_POP(3);
    return n_expr;
  }/*}}}*/

  // Expr -> Expr - Term
  void* Reduce_07() {/*{{{*/
    Expr *expr = (Expr*)GetGrammarSymbol(-3);
    Term *term = (Term*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    ENTRY_TYPE et = ReduceExpression(expr, term, " - ");
    /*---------------------------------------*/
    Expr *n_expr = new Expr(et.first, et.second);
    STACK_POP(3);
    return n_expr;
  }/*}}}*/

  // Expr -> Term
  void* Reduce_08() {/*{{{*/
    Term *term = (Term*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Expr *n_expr = new Expr(term->Entry(), term->Type());
    STACK_POP(1);
    return n_expr;
  }/*}}}*/

  // Term -> Term * Unary
  void* Reduce_09() {/*{{{*/
    Term *term = (Term*)GetGrammarSymbol(-3);
    Unary *unary = (Unary*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    ENTRY_TYPE et = ReduceExpression(term, unary, " * ");
    /*---------------------------------------*/
    Term *n_term = new Term(et.first, et.second);
    STACK_POP(3);
    return n_term;
  }/*}}}*/

  // Term -> Term / Unary
  void* Reduce_10() {/*{{{*/
    Term *term = (Term*)GetGrammarSymbol(-3);
    Unary *unary = (Unary*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    ENTRY_TYPE et = ReduceExpression(term, unary, " / ");
    /*---------------------------------------*/
    Term *n_term = new Term(et.first, et.second);
    STACK_POP(3);
    return n_term;
  }/*}}}*/

  // Term -> Unary
  void* Reduce_11() {/*{{{*/
    Unary *unary = (Unary*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Term *n_term = new Term(unary->Entry(), unary->Type());
    STACK_POP(1);
    return n_term;
  }/*}}}*/

  // Unary -> - Unary
  void* Reduce_12() {/*{{{*/
    Unary *unary = (Unary*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    ENTRY n_entry = new_entry();
    gen_inter(n_entry + " = "
        + " minus " + unary->Entry());
    /*---------------------------------------*/
    Unary *n_unary = new Unary(n_entry, unary->Type());
    STACK_POP(2);
    return n_unary;
  }/*}}}*/

  // Unary -> Factor
  void* Reduce_13() {/*{{{*/
    Factor *factor = (Factor*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Unary *n_unary =
      new Unary(factor->Entry(), factor->Type());
    STACK_POP(1);
    return n_unary;
  }/*}}}*/

  // Factor -> ( Expr )
  void* Reduce_14() {/*{{{*/
    Expr *expr = (Expr*)GetGrammarSymbol(-2);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Factor *n_factor =
      new Factor(expr->Entry(), expr->Type());
    STACK_POP(3);
    return n_factor;
  }/*}}}*/

  // Factor -> ID
  void* Reduce_15() {/*{{{*/
    Terminal *word = (Terminal*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    Id *id = env->GetId(word->Lexeme());
    if(id == NULL) {
      bin::Error(word->Lexeme() + " is not defined!");
      return NULL;
    }
    /*---------------------------------------*/
    Factor *n_factor =
      new Factor(id->Name(), id->Type());
    STACK_POP(1);
    return n_factor;
  }/*}}}*/

  // Factor -> INTEGER
  void* Reduce_16() {/*{{{*/
    Integer *_int = (Integer*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Factor *n_factor =
      new Factor(_int->Lexeme(), env->GetType("int"));
    STACK_POP(1);
    return n_factor;
  }/*}}}*/

  // Factor -> FLOAT
  void* Reduce_17() {/*{{{*/
    Real *_float = (Real*)GetGrammarSymbol(-1);
    /*------------Semantic Action------------*/
    /*---------------------------------------*/
    Factor *n_factor =
      new Factor(_float->Lexeme(), env->GetType("float"));
    STACK_POP(1);
    return n_factor;
  }/*}}}*/

}; // class Parser

} // namespace parser

#endif
