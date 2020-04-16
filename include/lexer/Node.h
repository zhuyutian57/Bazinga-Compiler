
#include "Stl.h"

#ifndef _NODE_H_
#define _NODE_H_

namespace lexer {

enum NodeType { LEAF, STAR, CAT, OR, PLUS, SUBT, LBR, RBR };

class Node {

public:
  Node(const NodeType);
  Node(const NodeType, Node*, Node*);
  Node(const char c);

  NodeType Nt() const;
  char Ch() const;
  Node* Ls() const;
  Node* Rs() const;
  
  void SetLs(Node*);
  void SetRs(Node*);

private:
  NodeType nt;
  char ch;
  Node *ls, *rs;
  
}; // class Node

} // namespace lexer

#endif
