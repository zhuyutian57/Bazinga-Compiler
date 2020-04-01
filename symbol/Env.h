
#include "Id.h"
#include "KeyWords.h"
#include "UnitSet.h"

#ifndef _ENV_H_
#define _ENV_H_

namespace symbol {

class Env {

public:
  Env() : pre(NULL) {
    types = new TYPE_MANAGER;
    (*types)["int"] = KeyWords::Int;
    (*types)["float"] = KeyWords::Float;
  }
  Env(Env *e) : pre(e) {
    types = e->types;
  }
  ~Env() {
    if(types != NULL) {
      delete types;
      types = NULL;
    }
  }

  void Put(const Terminal *word, Type *type) {
    if(table.find(word->Lexeme()) != table.end()) return;
    table[word->Lexeme()] = new Id(word->Lexeme(), type);
  }
  
  Id* GetId(const std::string& name) {
    for(Env *e = this; e; e = pre)
      if(e->table.find(name) != e->table.end())
        return e->table[name];
    return NULL;
  }

  bool InScope(const Terminal *word) {
    return table.find(word->Lexeme()) != table.end();
  }

  Type* GetType(const std::string& t) {
    return (*types)[t];
  }

private:
  SYMBOL_TABLE table;
  Env *pre;
  TYPE_MANAGER *types;

}; // class Env

} // namespace symbol

#endif
