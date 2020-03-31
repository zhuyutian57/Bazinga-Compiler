
#include <string>
#include <unordered_map>
#include <vector>

#include "Tag.h"
#include "Unit.h"

#ifndef _UNITSET_H_
#define _UNITSET_H_

namespace symbol {

class UnitSet {

public:
  UnitSet() : index(0) {/*{{{*/
    // Terminals
    Reserve("TYPE", Tag::TYPE);
    Reserve("ID", Tag::ID);
    Reserve("INTEGER", Tag::INTEGER);
    Reserve("FLOAT", Tag::FLOAT);
    Reserve('+'); Reserve('-');
    Reserve('*'); Reserve('/');
    Reserve(';'); Reserve('=');
    Reserve('('); Reserve(')');
    Reserve('$');
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
  ~UnitSet(){}/*}}}*/

  std::string operator[](const int& t) {/*{{{*/
    return tag_to_str[t];
  }
  int operator[](const std::string& s) {
    return str_to_tag[s];
  }/*}}}*/

  const int Size() { return units.size(); }
  const std::vector<Unit>& Units() { return units; }
  const int Index(const int& tag) { return index[tag]; }
  bool IsIndexed(const int& tag) {
    return tag != Tag::EPSILON && tag != Tag::PROGRAM;
  }
  bool IsIndexed(const Unit& unit) {
    return IsIndexed(unit.Tag());
  }

private:
  std::vector<Unit> units;
  std::unordered_map<int, int> index;
  std::unordered_map<int, std::string> tag_to_str;
  std::unordered_map<std::string, int> str_to_tag;

private:
   void Reserve(const std::string& s, int t) {/*{{{*/
     index[t] = units.size();
     units.push_back(Unit(t));
     if(t >= NONTERMINAL_BEGIN) index[t] -= 2;
     tag_to_str[t] = s;
     str_to_tag[s] = t;
  }
  void Reserve(const char ch) {
    Reserve(std::string("") + ch, ch);
  }/*}}}*/


}; // class Unitset

} // namespace symbol

#endif
