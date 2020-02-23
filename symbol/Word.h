
#include <string>

#include "Tag.h"
#include "Token.h"

#ifndef _WORD_H_
#define _WORD_H_

namespace symbol {

class Word : public Token {

public:
  Word(const std::string& s, int t)
    : lexeme(s), Token(t) {}

  const std::string& Lexe() const { return lexeme; }

private:
  std::string lexeme;

}; // class Word

} // namespace symbol

#endif
