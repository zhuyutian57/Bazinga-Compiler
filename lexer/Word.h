
#include <string>

#include "../symbol/Tag.h"
#include "../symbol/Unit.h"
using namespace symbol;

#ifndef _WORD_H_
#define _WORD_H_

namespace lexer {

class Word : public Unit {

public:
  Word(const std::string& s, int t)
    : lexeme(s), Unit(t) {}

  const std::string& Lexe() const { return lexeme; }

private:
  std::string lexeme;

}; // class Word

} // namespace lexer

#endif
