
#include <string>

#include "UnitSet.h"

#ifndef _ID_H_
#define _ID_H_

namespace symbol {

class Id {

public:
  Id(const std::string& s, terminals::Type *t)
    : name(s), type(t) {}
  ~Id() { delete type; }

  const std::string& Name() { return name; }

  terminals::Type* Type() { return type; }

private:
  std::string name;
  terminals::Type *type;

}; // class Id

} // namespace symbol

#endif
