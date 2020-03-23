
#include <string>

#include "../lexer/Type.h"

#ifndef _ID_H_
#define _ID_H_

namespace symbol {

class Id {

public:
  Id(const std::string& s, lexer::Type *t)
    : name(s), type(t) {}
  ~Id() { delete type; }

private:
  std::string name;
  lexer::Type *type;

}; // class Id

} // namespace symbol

#endif
