
#include "Node.h"

using namespace lexer;

Node::Node(const NodeType t)
  : nt(t) , ls(NULL), rs(NULL) {}
Node::Node(const NodeType t, Node* l, Node* r)
  : nt(t), ls(l), rs(r) {}
Node::Node(const char c)
  : nt(LEAF), ch(c), ls(NULL), rs(NULL) {}

NodeType  Node::Nt() const { return nt; }
char      Node::Ch() const { return ch; }
Node*     Node::Ls() const { return ls; }
Node*     Node::Rs() const { return rs; }
void      Node::SetLs(Node *t) { ls = t; }
void      Node::SetRs(Node *t) { rs = t; }
