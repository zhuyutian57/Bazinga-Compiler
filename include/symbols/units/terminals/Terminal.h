
#include "Stl.h"
#include "Tag.h"
#include "Unit.h"

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

namespace symbols {

inline namespace terminals {

class Terminal : public Unit {

public:
  Terminal(const char&);
  Terminal(const std::string&, int t);
  ~Terminal() {}

  const std::string& Lexeme() const;

private:
  std::string lexeme;

}; // class Terminal

} // namespace terminals

} // namespace symbols

#endif
