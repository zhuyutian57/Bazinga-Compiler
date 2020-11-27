
#include "UnitSet.h"

using namespace symbols;

UnitSet::UnitSet() {
  // Terminals
  Reserve("TYPE", Tag::TYPE);
  Reserve("ID", Tag::ID);
  Reserve("INTEGER", Tag::INTEGER);
  Reserve("FLOAT", Tag::REAL);
  Reserve("if", Tag::IF);
  Reserve("else", Tag::ELSE);
  Reserve("while", Tag::WHILE);
  Reserve("do", Tag::DO);
  Reserve("||", Tag::OR); Reserve("&&", Tag::AND);
  Reserve("<=", Tag::LE); Reserve(">=", Tag::GE);
  Reserve("==", Tag::EQ); Reserve("!=", Tag::NE);
  Reserve('+'); Reserve('-'); Reserve('*');
  Reserve('/'); Reserve(';'); Reserve('=');
  Reserve('('); Reserve(')'); Reserve('<');
  Reserve('>'); Reserve('!'); Reserve('$');
  Reserve("true", Tag::TRUE);
  Reserve("false", Tag::FALSE);
  // Nonterminals
  Reserve("Stmts",  Tag::STMTS);
  Reserve("Stmt",   Tag::STMT);
  Reserve("Bool",   Tag::BOOL);
  Reserve("Join",   Tag::JOIN);
  Reserve("Equal",  Tag::EQUAL);
  Reserve("Ineq",   Tag::INEQ);
  Reserve("Arith",  Tag::ARITH);
  Reserve("Term",   Tag::TERM);
  Reserve("Unary",  Tag::UNARY);
  Reserve("Factor", Tag::FACTOR);
  Reserve("Instr",    Tag::INSTR);
  Reserve("Jump", Tag::JUMP);
  // Not indexed
  Reserve("Epsilon", Tag::EPSILON);
  Reserve("Program", Tag::PROGRAM);
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
   tag_to_str[t] = s;
   str_to_tag[s] = t;
}
void UnitSet::Reserve(const char ch) {
  Reserve(std::string("") + ch, ch);
}
