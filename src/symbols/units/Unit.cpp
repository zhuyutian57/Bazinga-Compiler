
#include "Unit.h"

using namespace symbols;

Unit::Unit(const int t) : tag(t) {}
bool Unit::operator==(const Unit& unit) const {
  return tag == unit.tag;
}
bool Unit::operator<(const Unit& unit) const {
  return tag < unit.tag;
}

const TAG& Unit::Tag() const { return tag; }
