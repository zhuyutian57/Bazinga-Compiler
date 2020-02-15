
#include <map>
#include <string>
#include <vector>

#include "Ast.h"
#include "Node.h"

namespace lexer {

//(TODO) Implememt of DFA
// Build DFA directly from regular defination
class Automata {

public:
  Automata() {
    ast = new Ast;
  }

  void Gen_ast(const std::string& path) {
    ast->Regonize(path);
  }

private:
  

private:
  Ast *ast;

}; // Automata

} // lexer

