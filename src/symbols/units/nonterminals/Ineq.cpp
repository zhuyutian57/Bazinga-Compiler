
#include "Ineq.h"

using namespace symbols;

Ineq::Ineq(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::INEQ) {}
