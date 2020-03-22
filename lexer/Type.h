
#include <string>

#include "Terminal.h"

#ifndef _TYPE_H_
#define _TYPE_H_

namespace lexer {

class Type : public Terminal {

public:
  Type(const std::string& s, int tag, int w)
    : Terminal(s, tag), width(w) {}

  const int& Width() const { return width; }

private:
  int width;

}; // class Type

} // namespace lexer

#endif
