
#include <string>

#include "Word.h"

#ifndef _FLOAT_H_
#define _FLOAT_H_

namespace lexer {

class Float : public Word {

public:
  Float(const std::string& s)
    : Word(s, symbol::Tag::FLOAT),
      val(std::stof(s)) {} 

private:
  float val;

}; // class Float

} // namespace lexer

#endif
