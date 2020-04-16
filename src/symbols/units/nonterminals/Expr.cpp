
#include "Expr.h"

using namespace symbols;

Expr::Expr(const ENTRY& e, terminals::Type *tp)
  : Nonterminal(Tag::EXPR), type(tp), entry(e) {}
Expr::Expr(const ENTRY& e, terminals::Type *tp, const TAG& tag)
  : Nonterminal(tag), type(tp), entry(e) {}

const ENTRY& Expr::Entry() { return entry; }

terminals::Type* Expr::Type() { return type; }
