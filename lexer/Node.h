
#include <string>

namespace lexer {

void err() {
  std::cout << "What the fuck are you doing?" << '\n';
}

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
  
  NodeType& Nt() { return nt; }
  char& Ch() { return ch; }
  Node* Ls() { return ls; }
  Node* Rs() { return rs; }
  
  void Set_ls(Node *t) { ls = t; }
  void Set_rs(Node *t) { rs = t; }

private:
  NodeType nt;
  char ch;
  Node *ls, *rs;
  
}; // Node

} // lexer

