
#include "Expr.h"

using namespace symbols;

Expr::Expr(const ENTRY& e, Type *tp, const TAG& tag)
  : Unit(tag), type(tp), entry(e) {}

Expr::~Expr() {
  delete truelist;
  delete falselist;
}

const ENTRY& Expr::Entry() { return entry; }

Type* Expr::GetType() { return type; }

std::set<int>* Expr::TrueList() { return truelist; }

std::set<int>* Expr::FalseList() { return falselist; }

void Expr::AddLine(const int line, bool opt) {
  if(opt) truelist->insert(line);
  else falselist->insert(line);
}
