
#include "../symbol/Tag.h"

#ifndef _TOKEN_H_
#define _TOKEN_H_

namespace lexer {

class Token {

public:
  Token(const int t) : tag(t) {}

  const int& Tag() const { return tag; }

protected:
  int tag;

}; // class Token 

} // namespace lexer

#endif
