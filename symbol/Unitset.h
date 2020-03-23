
#include <string>
#include <unordered_map>
#include <vector>

#include "Tag.h"
#include "Unit.h"

#ifndef _UNITSET_H_
#define _UNITSET_H_

namespace symbol {

class Unitset {

public:
  Unitset() : index(0) {/*{{{*/
    // Terminals
    reserve("TYPE", Tag::TYPE);
    reserve("ID", Tag::ID);
    reserve("INTEGER", Tag::INTEGER);
    reserve("FLOAT", Tag::FLOAT);
    reserve('+'); reserve('-');
    reserve('*'); reserve('/');
    reserve(';'); reserve('=');
    reserve('('); reserve(')');
    reserve('$');
    reserve("Epsilon", Tag::EPSILON);
    // Nonterminals
    reserve("Program", Tag::PROGRAM);
    reserve("Stmts", Tag::STMTS);
    reserve("Stmt", Tag::STMT);
    reserve("Expr", Tag::EXPR);
    reserve("Term", Tag::TERM);
    reserve("Unary", Tag::UNARY);
    reserve("Factor", Tag::FACTOR);
  }
  ~Unitset(){}/*}}}*/

  std::string operator[](const int& t) {/*{{{*/
    return tag_to_str[t];
  }
  int operator[](const std::string& s) {
    return str_to_tag[s];
  }/*}}}*/

  const int Size() { return unitset.size(); }
  const std::vector<Unit>& Units() { return unitset; }
  const int Loc(const int& t) {
    const int& lo = index[t];
    if(t >= NONTERMINAL_BEGIN) return lo - 2;
    return lo;
  }

private:
  std::vector<Unit> unitset;
  std::unordered_map<int, int> index;
  std::unordered_map<int, std::string> tag_to_str;
  std::unordered_map<std::string, int> str_to_tag;

private:
   void reserve(const std::string& s, int t) {/*{{{*/
     index[t] = unitset.size();
     unitset.push_back(Unit(t));
     tag_to_str[t] = s;
     str_to_tag[s] = t;
  }
  void reserve(const char ch) {
    reserve(std::string("") + ch, ch);
  }/*}}}*/


}; // class Unitset

} // namespace symbol

#endif
