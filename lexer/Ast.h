
#include "Node.h"

#include "../bin/Bin.h"
using namespace bin;

#ifndef _AST_H_
#define _AST_H_

namespace lexer {

class Ast {

public:
  Ast() : leaf_size(-1), lexeme_tree(NULL) {/*{{{*/
    mpr["letters"] = BuildLetterTree();
    mpr["digits"] = BuildDigitTree();
  }
  ~Ast() {
    if(lexeme_tree != NULL)
      delete lexeme_tree;
  }/*}}}*/

  bool Build(const char* rd_path) {/*{{{*/
    if(!BuildTrees(rd_path)) return false;
    lexeme_tree = new Node(CAT, mpr["Lexeme"], new Node('#'));
    Info* root = Calculate(lexeme_tree);
    MoveSetToSet(root->firstpos, &root_firstpos);
    delete root;
    return true;
  }/*}}}*/

  int LeafSize() { return leaf_size; }
  const std::set<int>& RootFirstpos() {
    return root_firstpos;
  }
  const std::set<char>& Characters() {
    return characters;
  }
  char CharOfPosition(int i) { return posch[i]; }
  const std::vector<std::set<int>* >& Followpos() {
    return followpos;
  }
  
private:
  Node *lexeme_tree;
  // Reserve trees of every regular definations
  std::unordered_map<std::string, Node*> mpr;

  int leaf_size;
  std::set<int> root_firstpos;
  std::set<char> characters;
  std::unordered_map<int, char> posch;
  std::vector<std::set<int>* > followpos;

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

private:
  Node* CreateNode(const std::string& s) {/*{{{*/
    if(s == "(") return new Node(LBR);
    if(s == ")") return new Node(RBR);
    if(s == "|") return new Node(OR);
    if(s == "+") return new Node(PLUS);
    if(s == "*") return new Node(STAR);
    Node *p;
    if(s[0] == '[') p = BuildNotTree(s);
    else if(mpr.find(s) != mpr.end()) p = mpr[s];
    else if(s[0] == '\\') p = new Node(s[1]);
    else p = new Node(s[0]);
    return new Node(SUBT, p, NULL);
  }/*}}}*/

  Node* MergeNodes(std::stack<Node*>* S) {/*{{{*/
    Node *p, *del;
    del = S->top(); S->pop();
    p = del->Ls();
    delete del; // delete extra node labeled "SUBT"
    while(!S->empty() && S->top()->Nt() != LBR) {
      if(S->top()->Nt() == OR) {
        S->top()->SetRs(p);
        p = S->top(); S->pop();
        del = S->top(); S->pop();
        p->SetLs(del->Ls());
      } else {
        del = S->top(); S->pop();
        p = new Node(CAT, del->Ls(), p);
      }
      delete del;
    }
    return p;
  }/*}}}*/

  Node* BuildSubtrees(std::istringstream& ss) {/*{{{*/
    std::string x;
    std::stack<Node*>* S = new std::stack<Node*>;
    while(ss >> x) {
      Node *t = CreateNode(x);
      switch(t->Nt()) {
        case OR:
          S->push(new Node(SUBT, MergeNodes(S), NULL));
          break;
        case RBR:
          delete t;
          t = new Node(SUBT, MergeNodes(S), NULL);
          delete S->top(); S->pop();
          break;
        case LBR: break;
        case SUBT: break;
        default: // FOr PLUS and STAR
          t->SetLs(S->top()->Ls());
          delete S->top(); S->pop();
          t = new Node(SUBT, t, NULL);
      }
      S->push(t);
    }
    return MergeNodes(S);
  }/*}}}*/

  bool BuildTrees(const char* rd_path) {/*{{{*/
    std::cin.clear();
    freopen(rd_path, "r", stdin);
    std::string rd;
    while(std::getline(std::cin, rd)) {
      std::istringstream ss(rd); // make rd as words stream 
      std::string name, flag;
      ss >> name >> flag;
      if(flag != "->") {
        ErrorRegularDefination(name, ss);
        return false;
      }
      mpr[name] = BuildSubtrees(ss);
    }
    return true;
  }/*}}}*/

  Node* BuildOrTree(const std::string& s) {/*{{{*/
    Node* rt = NULL;
    for(auto ch : s) {
      if(rt == NULL) {
        rt = new Node(ch);
        continue;
      }
      rt = new Node(OR, rt, new Node(ch));
    }
    return rt;
  }/*}}}*/

  Node* BuildNotTree(const std::string& s) {/*{{{*/
    if(s[1] != '^') return NULL;
    std::set<char>* del = new std::set<char>;
    for(int i = 2; i < s.size() - 1; i++)
      del->insert(s[i]);
    if(s[2] >= '0' && s[2] <= '9')
      return BuildDigitTree(del);
    return BuildLetterTree(del);
  }/*}}}*/

  Node* BuildLetterTree(const std::set<char>* del = NULL) {/*{{{*/
    std::string s = "";
    for(char c = 'a'; c <= 'z'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    for(char c = 'A'; c <= 'Z'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    return BuildOrTree(s);
  }/*}}}*/

  Node* BuildDigitTree(const std::set<char>* del = NULL) {/*{{{*/
    std::string s = "";
    for(char c = '0'; c <= '9'; c++)
      if(del == NULL || del->find(c) == del->end())
        s += c;
    return BuildOrTree(s);
  }/*}}}*/

  void CalculateFollowPosition(/*{{{*/
      std::set<int>* in, std::set<int>* out) {
    for(auto i : (*in))
      for(auto n : (*out))
        followpos[i]->insert(n);
  }/*}}}*/

  Info* Calculate(const Node *p) {/*{{{*/
    Info* info = new Info();
    switch(p->Nt()) {
      case LEAF:
        ++leaf_size;
        info->nullable = false;
        info->firstpos->insert(leaf_size);
        info->lastpos->insert(leaf_size);
        posch[leaf_size] = p->Ch();
        characters.insert(p->Ch());
        followpos.push_back(new std::set<int>);
        break;
      case STAR: {
        Info* i_ls = Calculate(p->Ls());
        info->nullable = true;
        MoveSetToSet(i_ls->firstpos, info->firstpos);
        MoveSetToSet(i_ls->lastpos, info->lastpos);
        CalculateFollowPosition(info->lastpos, info->firstpos);
        delete i_ls;
        break;
      }
      case CAT: {
        Info *i_ls = Calculate(p->Ls());
        Info *i_rs = Calculate(p->Rs());
        info->nullable = (i_ls->nullable && i_rs->nullable);
        CalculateFollowPosition(i_ls->lastpos, i_rs->firstpos);
        MoveSetToSet(i_ls->firstpos, info->firstpos);
        MoveSetToSet(i_rs->lastpos, info->lastpos);
        if(i_ls->nullable)
          MoveSetToSet(i_rs->firstpos, info->firstpos);
        if(i_rs->nullable)
          MoveSetToSet(i_ls->lastpos, info->lastpos);
        delete i_ls, i_rs;
        break;
      }
      case OR: {
        Info *i_ls = Calculate(p->Ls());
        Info *i_rs = Calculate(p->Rs());
        info->nullable = (i_ls->nullable || i_rs->nullable);
        MoveSetToSet(i_ls->firstpos, info->firstpos);
        MoveSetToSet(i_rs->firstpos, info->firstpos);
        MoveSetToSet(i_ls->lastpos, info->lastpos);
        MoveSetToSet(i_rs->lastpos, info->lastpos);
        delete i_ls, i_rs;
        break;
      }
      case PLUS: break; //TODO add PLUS
      default: Error("Fail to build AST!\n");
    }
    return info;
  }/*}}}*/

}; // class Ast

} // namespace lexer

#endif
