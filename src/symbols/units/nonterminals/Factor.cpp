
#include "Factor.h"

using namespace symbols;

Factor::Factor(const ENTRY& entry, terminals::Type *type)
  : Expr(entry, type, Tag::FACTOR) {}
