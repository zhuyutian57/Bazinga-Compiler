
#include <string>

#include "Terminal.h"

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace lexer {

class Integer : public Terminal {

public:
  Integer(const std::string& s)
    : Terminal(s, symbol::Tag::INTEGER),
      val(std::stoi(s)) {} 

private:
  int val;

}; // class Integer

} // namespace lexer

#endif
