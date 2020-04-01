
#include <string>

#include "../Tag.h"
#include "../Unit.h"

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

namespace symbol {

inline namespace terminals {

class Terminal : public Unit {

public:
  Terminal(const char& ch)
    : Terminal(std::string("") + ch, ch) {}
  Terminal(const std::string& s, int t)
    : lexeme(s), Unit(t) {}

  const std::string& Lexeme() const { return lexeme; }

private:
  std::string lexeme;

}; // class Terminal

} // namespace terminals

} // namespace symbol

#endif
