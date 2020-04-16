
#include "Bin.h"
#include "Nonterminals.h"
#include "Tag.h"
#include "Terminals.h"
#include "Unit.h"

#ifndef _UNITSET_H_
#define _UNITSET_H_

namespace symbols {

class UnitSet {

public:
  UnitSet();
  ~UnitSet(){}

  std::string operator[](const int&);
  int operator[](const std::string&);

  const int Size();
  const std::vector<Unit>& Units();
  const int Index(const int&);
  bool IsIndexed(const int&);
  bool IsIndexed(const Unit& unit);

private:
  std::vector<Unit> units;
  std::unordered_map<int, int> index;
  std::unordered_map<int, std::string> tag_to_str;
  std::unordered_map<std::string, int> str_to_tag;

private:
  void Reserve(const std::string&, int);
  void Reserve(const char ch);

}; // class Unitset

} // namespace symbols

#endif
