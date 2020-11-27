
#include "Stmt.h"

using namespace symbols;

Stmt::Stmt() : Stmts(Tag::STMT), nextlist(NULL) {}
Stmt::~Stmt() { if(nextlist != NULL) delete nextlist; }

//TODO(optimize) diliver pointer rather than elements
void Stmt::AddInstr(INSTRLIST *list) {
  if(nextlist == NULL) nextlist = new INSTRLIST;
  bin::MoveSetToSet(list, nextlist);
}

std::set<int>* Stmt::NextList() { return nextlist; }
