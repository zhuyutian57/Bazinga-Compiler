
#include <iostream>
#include <string>

#include "Lexer.h"
#include "Action.h"

int main(int argc, char* argv[]) {
  if(argc < 3) {
    std::cerr<< "Missing parameters!" << '\n';
    return 0;
  }
  std::string op(argv[1]);
  if(op == "lexer") {
    lexer::Lexer *lex = new lexer::Lexer();
    lex->Build(argv[2]);
    if(argc == 4) lex->Analyze(argv[3]);
  } else if(op == "action") {
    parser::Action *ac = new parser::Action();
    ac->Build(argv[2]);
  } else if(op == "parser") {
    //TODO
  } else std::cout << "Incorrect parameter!" << '\n';
  return 0;
}
