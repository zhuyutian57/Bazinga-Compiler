
#include "Bool.h"

using namespace symbols;

Bool::Bool(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::BOOL) {}
