
#include "Ast.h"

#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

namespace lexer {

class Automata {

public:
  Automata();
  ~Automata();

  void Build(const char*);
  void Reset();
  DNF_STATE Goto(char ch);
  bool Accepted();

private:
  Ast *ast;
  
  int state_size;
  DNF_STATE start, current_state;
  std::vector<AST_LEAVES_SET*> ast_leaf_sets;
  std::set<char> alphabet;
  std::map<DFA_EDGE, DNF_STATE> edges;
  std::set<DNF_STATE> accepted_states;
 
  struct Hash {
    std::size_t operator()(const AST_LEAVES_SET& t) const {
      const std::size_t MOD = 1000000007;
      const std::size_t B = 3;
      std::size_t W = 1, C = 0;
      std::size_t h = 998244353;
      for(auto x : t) {
        for(; C < x; C++) W = (W * B) % MOD;
        h = (h * W) % MOD;
      }
      return h;
    }
  }; //struct Hash

private:
  void BuildDFA(const std::vector<std::set<int>*>&);
  void Informations();

}; // class Automata

} // namespace lexer

#endif
