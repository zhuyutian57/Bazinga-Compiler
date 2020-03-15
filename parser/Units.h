
#include <string>
#include <unordered_map>
#include <vector>

#include "../symbol/Tag.h"
#include "../symbol/Unit.h"
using namespace symbol;

#ifndef _UNITS_H_
#define _UNITS_H_

namespace parser {

#define NONTERMINAL_BEGIN 401

class Units {

public:
  Units() {
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
    reserve("ADD_ID", Tag::ADD_ID);
    reserve("ID_EXIST", Tag::ID_EXIST);
    // Test
    reserve("P", Tag::P);
    reserve("S", Tag::S);
    reserve("L", Tag::L);
    reserve("R", Tag::R);
  }
  ~Units(){}

  std::string operator[](const int& t) {
    return tag_to_str[t];
  }
  int operator[](const std::string& s) {
    return str_to_tag[s];
  }

  const int Units_size() { return unitset.size(); }
  const std::vector<Unit>& Unitset() { return unitset; }
  const int Loc(const int t) { return pos[t]; }

private:
  std::vector<Unit> unitset;
  std::unordered_map<int, int> pos;
  std::unordered_map<int, std::string> tag_to_str;
  std::unordered_map<std::string, int> str_to_tag;

private:
  void reserve(const char ch) {/*{{{*/
    pos[int(ch)] = unitset.size();
    unitset.push_back(Unit(ch));
    tag_to_str[int(ch)] = std::string("") + ch;
    str_to_tag[std::string("") + ch] = int(ch);
  }
  void reserve(const std::string& s, int t) {
    pos[t] = unitset.size();
    unitset.push_back(Unit(t));
    tag_to_str[t] = s;
    str_to_tag[s] = t;
  }/*}}}*/

}; // class Units

} // namespace parser

#endif
