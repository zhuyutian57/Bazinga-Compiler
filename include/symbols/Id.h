
#include "Stl.h"
#include "UnitSet.h"

#ifndef _ID_H_
#define _ID_H_

namespace symbols {

class Id {

public:
  Id(const std::string&, terminals::Type*);
  ~Id();

  const std::string& Name();
  terminals::Type* Type();

private:
  std::string name;
  terminals::Type *type;

}; // class Id

} // namespace symbols

#endif
