
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Ast.h"
#include "Info.h"

namespace lexer {

//(TODO) Implememt of DFA
// Build DFA directly from regular defination
class Automata {

public:
  Automata() : leaf_size(-1) {
    ast = new Ast;
    characters = new std::set<char>;
    posch = new std::map<int, char>;
    followpos.clear();
  }

  void Build(const char* path) {
    ast->Regonize(path);
    calculate();
  }

  // For tests
  std::map<int, char>* Posch() { return posch; }
  std::vector<std::set<int>* >& Followpos() { return followpos; }

private:

  // Insert n in "out" to followpos(i) & (i in "in")
  void cal_followpos(std::set<int>* in, std::set<int>* out) {
    for(auto i : (*in))
      for(auto n : (*out))
        followpos[i]->insert(n);
  }

  void move(std::set<int>* in, std::set<int>* out) {
    for(auto e : (*out)) in->insert(e);
  }

  Info* cal_followpos(Node *p) {
    Info* info = new Info();
    switch(p->Nt()) {
      case LEAF:
        ++leaf_size;
        info->Set_nullable(false);
        info->Firstpos()->insert(leaf_size);
        info->Lastpos()->insert(leaf_size);
        (*posch)[leaf_size] = p->Ch();
        characters->insert(p->Ch());
        followpos.push_back(new std::set<int>);
        break;
      case STAR: {
        Info* i_ls = cal_followpos(p->Ls());
        info->Set_nullable(true);
        move(info->Firstpos(), i_ls->Firstpos());
        move(info->Lastpos(), i_ls->Lastpos());
        cal_followpos(info->Lastpos(), info->Firstpos());
        delete i_ls;
        break;
      }
      case CAT: {
        Info *i_ls = cal_followpos(p->Ls());
        Info *i_rs = cal_followpos(p->Rs());
        info->Set_nullable(i_ls->Nullable() && i_rs->Nullable());
        cal_followpos(i_ls->Lastpos(), i_rs->Firstpos());
        move(info->Firstpos(), i_ls->Firstpos());
        move(info->Lastpos(), i_rs->Lastpos());
        if(i_ls->Nullable())
          move(info->Firstpos(), i_rs->Firstpos());
        if(i_rs->Nullable())
          move(info->Lastpos(), i_ls->Lastpos());
        delete i_ls, i_rs;
        break;
      }
      case OR: {
        Info *i_ls = cal_followpos(p->Ls());
        Info *i_rs = cal_followpos(p->Rs());
        info->Set_nullable(i_ls->Nullable() || i_rs->Nullable());
        move(info->Firstpos(), i_ls->Firstpos());
        move(info->Firstpos(), i_rs->Firstpos());
        move(info->Lastpos(), i_ls->Lastpos());
        move(info->Lastpos(), i_rs->Lastpos());
        delete i_ls, i_rs;
        break;
      }
      case PLUS: break; //TODO add PLUS
      default:
        err();
    }
    return info;
  }

  void calculate() {
    Info* root = cal_followpos(ast->Lexeme_tree());
    start = root->Firstpos();
    root->Set_firstpos(NULL);
    delete root;
  }

private:
  int leaf_size;
  Ast *ast;
  std::set<char>* characters;
  std::set<int>* start;
  std::map<int, char>* posch;
  std::vector<std::set<int>* > followpos;

}; // Automata

} // lexer

