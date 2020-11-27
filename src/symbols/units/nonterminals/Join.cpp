
#include "Join.h"

using namespace symbols;

Join::Join(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::JOIN) {}
