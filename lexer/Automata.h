
#include "Ast.h"

#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

namespace lexer {

class Automata {

public:
  Automata() {/*{{{*/
    ast = new Ast;
  }
  ~Automata() {
    delete ast;
  }/*}}}*/

  void Build(const char* rd_path) {/*{{{*/
    ast->Build(rd_path);
    MoveSetToSet(&ast->Characters(), &alphabet);
    ast_leaf_sets.push_back(new AST_LEAVES_SET);
    MoveSetToSet(&ast->RootFirstpos(), ast_leaf_sets[0]);
    start = 0;
    state_size = 1;
    BuildDFA(ast->Followpos());
    Informations();
  }/*}}}*/

  void Reset() { current_state = start; }
  DNF_STATE Goto(char ch) {
    DFA_EDGE u = std::make_pair(current_state, ch);
    if(edges.find(u) == edges.end())
      return -1;
    current_state = edges[u];
    return current_state;
  }
  bool Accepted() {
    return accepted_states.find(current_state)
      != accepted_states.end();
  }

private:
  Ast *ast;
  
  int state_size;
  DNF_STATE start, current_state;
  std::vector<AST_LEAVES_SET*> ast_leaf_sets;
  std::set<char> alphabet;
  std::map<DFA_EDGE, DNF_STATE> edges;
  std::set<DNF_STATE> accepted_states;
 
  struct Hash {/*{{{*/
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
  }; //struct Hash}}}

private:
  void BuildDFA(const std::vector<std::set<int>*>& followpos) {/*{{{*/
    const int END_POS = ast->LeafSize();
    std::unordered_map<AST_LEAVES_SET, DNF_STATE, Hash> mps;
    std::unordered_map<DNF_STATE, bool> vis;
    std::queue<DNF_STATE> Q;
    Q.push(start);
    mps[(*ast_leaf_sets[0])] = start;
    // u -> v
    for(DNF_STATE u; !Q.empty(); ) {
      u = Q.front(); Q.pop();
      if(vis.find(u) != vis.end()) continue;
      vis[u] = true;
      if(ast_leaf_sets[u]->find(END_POS)
          != ast_leaf_sets[u]->end())
        accepted_states.insert(u);
      for(auto ch : alphabet) {
        AST_LEAVES_SET *v = new AST_LEAVES_SET;
        for(auto p : (*ast_leaf_sets[u]))
          if(ast->CharOfPosition(p) == ch)
            MoveSetToSet(followpos[p], v);
        if(v->empty()) { delete v; continue; }
        DNF_STATE t; // Get id of v
        if(mps.find(*v) == mps.end()) {
          t = mps[*v] = state_size++;
          ast_leaf_sets.push_back(v); Q.push(t);
        } else { t = mps[*v]; delete v; }
        edges[std::make_pair(u, ch)] = t;
      }
    }
  }/*}}}*/

  void Informations() {/*{{{*/
    std::cout << "============= DFA =============\n";
    std::cout << " State size : "<< state_size << '\n';
    std::cout << " Start state : " << start << '\n';
    std::cout << " Alphabet : " << alphabet.size() << ' ';
    for(auto ch : alphabet)
      std::cout << ' ' << ch;    
    std::cout << '\n';
    std::cout << " Accepted states :";
    for(auto s : accepted_states)
      std::cout << ' ' << s;
    std::cout << '\n';
    std::cout << "============= DFA =============\n";
  }/*}}}*/


}; // class Automata

} // namespace lexer

#endif
