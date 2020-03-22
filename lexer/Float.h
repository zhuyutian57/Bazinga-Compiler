
#include <string>

#include "Terminal.h"

#ifndef _FLOAT_H_
#define _FLOAT_H_

namespace lexer {

class Float : public Terminal {

public:
  Float(const std::string& s)
    : Terminal(s, symbol::Tag::FLOAT),
      val(std::stof(s)) {} 

private:
  float val;

}; // class Float

} // namespace lexer

#endif
