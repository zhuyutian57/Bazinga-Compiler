
#include "Unary.h"

using namespace symbols;

Unary::Unary(const ENTRY& entry, terminals::Type *type)
  : Expr(entry, type, Tag::UNARY) {}
