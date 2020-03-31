
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
  std::unordered_map<std::string, lexer::Type*>

class Env {

public:
  Env() : pre(NULL) {
    table = new Table;
    types = new TYPE_MANAGER;
  }
  Env(Env *e) : pre(e) {
    table = new Table;
    types = e->types;
  }
  ~Env() {}

  void Put(const lexer::Terminal *word,
      lexer::Type *type) {
    if(table->find(word->Lexeme()) != table->end())
      return;
    if(types->find(type->Lexeme()) == types->end())
      (*types)[type->Lexeme()] = type;
    (*table)[word->Lexeme()] = new Id(word->Lexeme(), type);
  }
  
  Id* Get(const std::string& name) {
    for(Env *e = this; e; e = pre)
      if(e->table->find(name) != e->table->end())
        return (*e->table)[name];
    return NULL;
  }

  bool Find(const lexer::Terminal *word) {
    return table->find(word->Lexeme()) != table->end();
  }

  lexer::Type* Type(const std::string& t) {
    return (*types)[t];
  }

private:
  Table *table;
  Env *pre;
  TYPE_MANAGER *types;

}; // class Env

} // namespace symbol

#endif
