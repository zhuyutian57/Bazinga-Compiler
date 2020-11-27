
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
  Type* GetType();

private:
  std::string name;
  Type *type;

}; // class Id

} // namespace symbols

#endif
