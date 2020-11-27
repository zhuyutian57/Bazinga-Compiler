
#include "Term.h"

using namespace symbols;

Term::Term(const ENTRY& entry, Type *type)
  : Expr(entry, type, Tag::TERM) {}
