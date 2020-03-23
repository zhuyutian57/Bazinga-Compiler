
#ifndef _UNIT_H_
#define _UNIT_H_

namespace symbol {

#define TAG int
#define NONTERMINAL_BEGIN 401

class Unit {

public:
  Unit(const int t) : tag(t) {}
  bool operator==(const Unit& unit) const {
    return tag == unit.tag;
  }
  bool operator<(const Unit& unit) const {
    return tag < unit.tag;
  }

  const int& Tag() const { return tag; }

protected:
  int tag;

}; // class Unit 

} // namespace symbol

#endif

