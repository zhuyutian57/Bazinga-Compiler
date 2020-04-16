
#include "Messages.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
  parser::Parser *compiler = new parser::Parser();
  bin::Print("Building.......");
  compiler->Build(
      "D:\\GitHub\\Bazinga-Compiler\\config\\regular_defination.rd",
      "D:\\GitHub\\Bazinga-Compiler\\config\\grammars.cfg");
  bin::Print("Building Finish!");
  bin::Print("Analyzing........");
  compiler->Analyze("D:\\GitHub\\Bazinga-Compiler\\config\\1.bzg");
  return 0;
}

