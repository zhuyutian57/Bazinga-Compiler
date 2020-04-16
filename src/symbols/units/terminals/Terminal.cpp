
#include "Terminal.h"

using namespace symbols;

Terminal::Terminal(const char& ch)
  : Terminal(std::string("") + ch, ch) {}
Terminal::Terminal(const std::string& s, int t)
  : lexeme(s), Unit(t) {}

const std::string& Terminal::Lexeme() const { return lexeme; }
