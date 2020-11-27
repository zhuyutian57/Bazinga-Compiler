
#include "Stl.h"
#include "Tag.h"
#include "Unit.h"

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

namespace symbols {

inline namespace terminals {

class Word : public Unit {

public:
  Word(const char&);
  Word(const std::string&, int t);
  ~Word() {}

  const std::string& Lexeme() const;

private:
  std::string lexeme;

}; // class Word

} // namespace terminals

} // namespace symbols

#endif
