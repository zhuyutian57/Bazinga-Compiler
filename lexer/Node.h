
#include <iostream>
#include <string>

#ifndef _NODE_H_
#define _NODE_H_

namespace lexer {

// AST node
enum NodeType {
  LEAF, STAR, CAT, OR, PLUS,
  SUBT, LBR, RBR }; // Used for build trees

class Node {

public:
  Node(NodeType t, Node* l = NULL, Node* r = NULL)
    : nt(t), ls(l), rs(r) {}
  Node(char c)
    : nt(LEAF), ch(c), ls(NULL), rs(NULL) {}
  
  NodeType Nt() const { return nt; }
  char Ch() const { return ch; }
  Node* Ls() const { return ls; }
  Node* Rs() const { return rs; }
  
  void Set_ls(Node *t) { ls = t; }
  void Set_rs(Node *t) { rs = t; }

private:
  NodeType nt;
  char ch;
  Node *ls, *rs;
  
}; // class Node

} // namespace lexer

#endif
