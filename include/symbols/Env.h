
#include "Id.h"
#include "KeyWords.h"
#include "UnitSet.h"

#ifndef _ENV_H_
#define _ENV_H_

namespace symbols {

class Env {

public:
  Env();
  Env(Env*);
  ~Env();

  void Put(const Terminal*, Type*);
  Id* GetId(const std::string&);
  bool InScope(const Terminal*);
  Type* GetType(const std::string&);

private:
  SYMBOL_TABLE table;
  Env *pre;
  TYPE_MANAGER *types;

}; // class Env

} // namespace symbols

#endif
