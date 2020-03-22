
#include <string>

#include "../symbol/Tag.h"
#include "../symbol/Unit.h"
using namespace symbol;

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

namespace lexer {

class Terminal : public Unit {

public:
  Terminal(const char& ch)
    : Terminal(std::string("") + ch, ch) {}
  Terminal(const std::string& s, int t)
    : lexeme(s), Unit(t) {}

  const std::string& Lexe() const { return lexeme; }

private:
  std::string lexeme;

}; // class Terminal

} // namespace lexer

#endif
