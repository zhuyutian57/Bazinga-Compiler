
#include "Word.h"

using namespace symbols;

Word::Word(const char& ch)
  : Word(std::string("") + ch, ch) {}
Word::Word(const std::string& s, int t)
  : lexeme(s), Unit(t) {}

const std::string& Word::Lexeme() const { return lexeme; }
