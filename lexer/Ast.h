
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "Node.h"

#include "../message/Message.h"

#ifndef _AST_H_
#define _AST_H_

namespace lexer {

template<typename T>  
void move_set2set(std::set<T>* in, 
    const std::set<T>* out) {
  for(auto e : (*out)) in->insert(e);
}

// Abstract Syntax Tree 
class Ast {

private:  
  struct Info {
    bool nullable;
    std::set<int> *firstpos, *lastpos;
    Info() {
     firstpos = new std::set<int>;
     lastpos = new std::set<int>;
    }
    ~Info() {
      delete firstpos, lastpos;
    }
  }; // struct Info


public:
  Ast() : leaf_size(-1), lexeme_tree(NULL) {
    mpr["letters"] = build_letters_tree();
    mpr["digits"] = build_digits_tree();
    root_firstpos = new std::set<int>;
    posch = new std::unordered_map<int, char>;
    characters = new std::set<char>;
  }
  ~Ast() {
    delete posch, characters;
    delete root_firstpos;
    if(lexeme_tree != NULL)
      delete lexeme_tree;
  }

  bool Build(const char* rd_path) {
    if(!build_trees(rd_path)) return false;
    lexeme_tree = new Node(CAT, mpr["Lexeme"], new Node('#'));
    Info* root = calculate(lexeme_tree);
    move_set2set(root_firstpos, root->firstpos);
    delete root;
    return true;
  }

  int Leaf_size() { return leaf_size; }
  const std::set<int>* Root_firstpos() {
    return root_firstpos;
  }
  const std::set<char>* Characters() {
    return characters;
  }
  char Posch(int i) {
    return (*posch)[i];
  }
  const std::vector<std::set<int>* >& Followpos() {
    return followpos;
  }
  
private:
  Node *lexeme_tree;
  // Reserve trees of every regular definations
  std::unordered_map<std::string, Node*> mpr;

  int leaf_size;
  std::set<int>* root_firstpos;
  std::set<char>* characters;
  std::unordered_map<int, char>* posch;
  std::vector<std::set<int>* > followpos;

private:
  //TODO So ugly, make it beautiful
  Node* create_node(const std::string& s) {
    if(s == "(") return new Node(LBR);
    if(s == ")") return new Node(RBR);
    if(s == "|") return new Node(OR);
    if(s == "+") return new Node(PLUS);
    if(s == "*") return new Node(STAR);
    Node *p;
    if(s[0] == '[') p = build_not_tree(s);
    else if(mpr.find(s) != mpr.end()) p = mpr[s];
    else if(s[0] == '\\') p = new Node(s[1]);
    else p = new Node(s[0]);
    return new Node(SUBT, p, NULL);
  }

  Node* merge_nodes(std::stack<Node*>* S) {
    Node *p, *del;
    del = S->top(); S->pop();
    p = del->Ls();
    delete del; // delete extra node labeled "SUBT"
    while(!S->empty() && S->top()->Nt() != LBR) {
      if(S->top()->Nt() == OR) {
        S->top()->Set_rs(p);
        p = S->top(); S->pop();
        del = S->top(); S->pop();
        p->Set_ls(del->Ls());
      } else {
        del = S->top(); S->pop();
        p = new Node(CAT, del->Ls(), p);
      }
      delete del;
    }
    return p;
  }

  Node* build_subtrees(std::istringstream& ss) {
    std::string x;
    std::stack<Node*>* S = new std::stack<Node*>;
    while(ss >> x) {
      Node *t = create_node(x);
      switch(t->Nt()) {
        case OR:
          S->push(new Node(SUBT, merge_nodes(S), NULL));
          break;
        case RBR:
          delete t;
          t = new Node(SUBT, merge_nodes(S), NULL);
          delete S->top(); S->pop();
          break;
        case LBR: break;
        case SUBT: break;
        default: // FOr PLUS and STAR
          t->Set_ls(S->top()->Ls());
          delete S->top(); S->pop();
          t = new Node(SUBT, t, NULL);
      }
      S->push(t);
    }
    return merge_nodes(S);
  }

  bool build_trees(const char* path) {
    freopen(path, "r", stdin);
    std::string rd;
    while(std::getline(std::cin, rd)) {
      std::istringstream ss(rd); // make rd as words stream 
      std::string name, flag;
      ss >> name >> flag;
      if(flag != "->") {
        message::err_rd(name, ss);
        return false;
      }
      mpr[name] = build_subtrees(ss);
    }
    return true;
  }

  Node* build_or_tree(const std::string& s) {
    Node* rt = NULL;
    for(auto ch : s) {
      if(rt == NULL) {
        rt = new Node(ch);
        continue;
      }
      rt = new Node(OR, rt, new Node(ch));
    }
    return rt;
  }

  Node* build_not_tree(const std::string& s) {
    if(s[1] != '^') return NULL;
    std::set<char>* del = new std::set<char>;
    for(int i = 2; i < s.size() - 1; i++)
      del->insert(s[i]);
    if(s[2] >= '0' && s[2] <= '9')
      return build_digits_tree(del);
    return build_letters_tree(del);
  }

  Node* build_letters_tree(const std::set<char>* del = NULL) {
    std::string s = "";
    for(char c = 'a'; c <= 'z'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    for(char c = 'A'; c <= 'Z'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    return build_or_tree(s);
  }

  Node* build_digits_tree(const std::set<char>* del = NULL) {
    std::string s = "";
    for(char c = '0'; c <= '9'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    return build_or_tree(s);
  }

  // ========================================================
  // Calculate followpos

  void cal_followpos(std::set<int>* in, std::set<int>* out) {
    for(auto i : (*in))
      for(auto n : (*out))
        followpos[i]->insert(n);
  }

  Info* calculate(const Node *p) {
    Info* info = new Info();
    switch(p->Nt()) {
      case LEAF:
        ++leaf_size;
        info->nullable = false;
        info->firstpos->insert(leaf_size);
        info->lastpos->insert(leaf_size);
        (*posch)[leaf_size] = p->Ch();
        characters->insert(p->Ch());
        followpos.push_back(new std::set<int>);
        break;
      case STAR: {
        Info* i_ls = calculate(p->Ls());
        info->nullable = true;
        move_set2set(info->firstpos, i_ls->firstpos);
        move_set2set(info->lastpos, i_ls->lastpos);
        cal_followpos(info->lastpos, info->firstpos);
        delete i_ls;
        break;
      }
      case CAT: {
        Info *i_ls = calculate(p->Ls());
        Info *i_rs = calculate(p->Rs());
        info->nullable = (i_ls->nullable && i_rs->nullable);
        cal_followpos(i_ls->lastpos, i_rs->firstpos);
        move_set2set(info->firstpos, i_ls->firstpos);
        move_set2set(info->lastpos, i_rs->lastpos);
        if(i_ls->nullable)
          move_set2set(info->firstpos, i_rs->firstpos);
        if(i_rs->nullable)
          move_set2set(info->lastpos, i_ls->lastpos);
        delete i_ls, i_rs;
        break;
      }
      case OR: {
        Info *i_ls = calculate(p->Ls());
        Info *i_rs = calculate(p->Rs());
        info->nullable = (i_ls->nullable || i_rs->nullable);
        move_set2set(info->firstpos, i_ls->firstpos);
        move_set2set(info->firstpos, i_rs->firstpos);
        move_set2set(info->lastpos, i_ls->lastpos);
        move_set2set(info->lastpos, i_rs->lastpos);
        delete i_ls, i_rs;
        break;
      }
      case PLUS: break; //TODO add PLUS
      default: message::error("Fail to build AST!\n");
    }
    return info;
  }

}; // class Ast

} // namespace lexer

#endif
