
#include "Bin.h"
#include "Node.h"

#ifndef _AST_H_
#define _AST_H_

namespace lexer {

class Ast {

public:
  Ast();
  ~Ast();

  bool Build(const char*);
  int LeafSize();
  const std::set<int>& RootFirstpos();
  const std::set<char>& Characters();
  char CharOfPosition(int);
  const std::vector<std::set<int>* >& Followpos();
  
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
  Node* CreateNode(const std::string&);
  Node* MergeNodes(std::stack<Node*>*);
  Node* BuildSubtrees(std::istringstream&);
  bool  BuildTrees(const char*);
  Node* BuildOrTree(const std::string&);
  Node* BuildNotTree(const std::string&);
  Node* BuildLetterTree(const std::set<char>*);
  Node* BuildDigitTree(const std::set<char>*);
  void  CalculateFollowPosition(std::set<int>*, std::set<int>*);
  Info* Calculate(const Node*);

}; // class Ast

} // namespace lexer

#endif
