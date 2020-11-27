
#include "Equal.h"

using namespace symbols;

Equal::Equal(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::EQUAL) {}
