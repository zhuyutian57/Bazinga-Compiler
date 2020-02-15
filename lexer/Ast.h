
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "Container.h"
#include "Node.h"

namespace lexer {

// Abstract Syntax Tree 
class Ast {

public:
  Ast() {
    mpr["letters"] = build_letters_tree();
    mpr["digits"] = build_digits_tree();
  }

  void Regonize(const char* path) {
    build_trees(path);
  }

  Node* Tree(const std::string& s) {
    return mpr[s];
  }

private:
  
  void err() {
    std::cout << "What the fuck are you doing?" << '\n';
  }

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

  Node* build(std::istringstream& ss) {
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

  void build_trees(const char* path) {
    freopen(path, "r", stdin);
    std::string rd;
    while(std::getline(std::cin, rd)) {
      std::istringstream ss(rd); // make rd as words stream 
      std::string name, flag;
      ss >> name >> flag;
      if(flag != "->") { err(); return; }
      mpr[name] = build(ss);
    } 
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

private:
  std::map<std::string, Node*> mpr; // Reserve trees of every regular definations

}; // Ast

} // lexer

