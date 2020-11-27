
#include "Arith.h"

using namespace symbols;

Arith::Arith(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::ARITH) {}
