
#include <string>

#include "Word.h"

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace lexer {

class Integer : public Word {

public:
  Integer(const std::string& s)
    : Word(s, symbol::Tag::INTEGER),
      val(std::stoi(s)) {} 

private:
  int val;

}; // class Integer

} // namespace lexer

#endif
