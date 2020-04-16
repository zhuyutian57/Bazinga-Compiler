
#include "UnitSet.h"

using namespace symbols;

UnitSet::UnitSet() {
  // Terminals
  Reserve("TYPE", Tag::TYPE);
  Reserve("ID", Tag::ID);
  Reserve("INTEGER", Tag::INTEGER);
  Reserve("FLOAT", Tag::REAL);
  Reserve('+'); Reserve('-');
  Reserve('*'); Reserve('/');
  Reserve(';'); Reserve('=');
  Reserve('('); Reserve(')');
  Reserve("$", Tag::END);
  Reserve("Epsilon", Tag::EPSILON);
  // Nonterminals
  Reserve("Program", Tag::PROGRAM);
  Reserve("Stmts", Tag::STMTS);
  Reserve("Stmt", Tag::STMT);
  Reserve("Expr", Tag::EXPR);
  Reserve("Term", Tag::TERM);
  Reserve("Unary", Tag::UNARY);
  Reserve("Factor", Tag::FACTOR);
  // Tests
  //Reserve("P", Tag::P);
  //Reserve("S", Tag::S);
  //Reserve("L", Tag::L);
  //Reserve("R", Tag::R);
}

std::string UnitSet::operator[](const int& t) {
  return tag_to_str[t];
}
int UnitSet::operator[](const std::string& s) {
  return str_to_tag[s];
}

const int UnitSet::Size() { return units.size(); }
const std::vector<Unit>& UnitSet::Units() { return units; }
const int UnitSet::Index(const int& tag) { return index[tag]; }
bool UnitSet::IsIndexed(const int& tag) {
  return tag != Tag::EPSILON && tag != Tag::PROGRAM;
}
bool UnitSet::IsIndexed(const Unit& unit) {
  return IsIndexed(unit.Tag());
}

void UnitSet::Reserve(const std::string& s, int t) {
   index[t] = units.size();
   units.push_back(Unit(t));
   if(t >= NONTERMINAL_BEGIN) index[t] -= 2;
   tag_to_str[t] = s;
   str_to_tag[s] = t;
}
void UnitSet::Reserve(const char ch) {
  Reserve(std::string("") + ch, ch);
}
