
#include "Env.h"

using namespace symbols;

Env::Env() : pre(NULL) {
  types = new TYPE_MANAGER;
  (*types)["int"] = KeyWords::Int;
  (*types)["float"] = KeyWords::Float;
}
Env::Env(Env *e) : pre(e) { types = e->types; }
Env::~Env() {
  if(types != NULL) {
    delete types;
    types = NULL;
  }
}

void Env::Put(const Terminal *word, Type *type) {
  if(table.find(word->Lexeme()) != table.end()) return;
  table[word->Lexeme()] = new Id(word->Lexeme(), type);
}

Id* Env::GetId(const std::string& name) {
  for(Env *e = this; e; e = pre)
    if(e->table.find(name) != e->table.end())
      return e->table[name];
  return NULL;
}

bool Env::InScope(const Terminal *word) {
  return table.find(word->Lexeme()) != table.end();
}

Type* Env::GetType(const std::string& t) {
  return (*types)[t];
}
