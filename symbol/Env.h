
#include <string>
#include <unordered_map>

#include "Id.h"

#include "../lexer/Type.h"

#ifndef _ENV_H_
#define _ENV_H_

namespace symbol {

#define Table \
  std::unordered_map<std::string, Id*>
#define TYPE_MANAGER \
  std::unordered_map<TAG, lexer::Type*>

class Env {

public:
  Env() : pre(NULL) {
    table = new Table;
    types = new TYPE_MANAGER;
  }
  Env(Env *e) : pre(e) {
    table = new Table;
  }
  ~Env() {}

  void Put(const std::string& name,
      lexer::Type *type) {
    if(table->find(name) != table->end())
      return;
    if(types->find(type->Tag()) != types->end())
      (*types)[type->Tag()] = type;
    (*table)[name] = new Id(name, type);
  }
  
  Id* Get(const std::string& name) {
    for(Env *e = this; e; e = pre)
      if(e->table->find(name) != e->table->end())
        return (*e->table)[name];
    return NULL;
  }

  bool find(const std::string& name) {
    return table->find(name) != table->end();
  }

  lexer::Type* Type(const TAG& t) {
    return (*types)[t];
  }

private:
  Table *table;
  Env *pre;
  static TYPE_MANAGER *types;

}; // class Env

} // namespace symbol

#endif
