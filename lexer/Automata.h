
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Ast.h"

#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

namespace lexer {

#define DNF_STATE int
#define Edge std::pair<DNF_STATE, char>
#define Pos_set std::set<int>

// Build DFA directly from regular defination
class Automata {

private:
  struct Hash {
    std::size_t operator()(const Pos_set& t) const {
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

public:
  Automata() {
    ast = new Ast;
    pos_sets = new std::vector<Pos_set*>;
    alphabet = new std::set<char>;
    edges = new std::map<Edge, DNF_STATE>;
    acc = new std::set<DNF_STATE>;
  
  }
  ~Automata() {
    delete ast, alphabet, edges, acc;
    delete [] pos_sets;
  }

  void Build(const char* rd_path) {
    ast->Build(rd_path);
    move_set2set(alphabet, ast->Characters());
    pos_sets->push_back(new Pos_set);
    move_set2set((*pos_sets)[0], ast->Root_firstpos());
    start = 0;
    state_size = 1;
    build_dfa(ast->Followpos());
    info_automata(
        state_size, start, alphabet, acc);
  }

  void Reset() { cur = start; }

  DNF_STATE Goto(char ch) {
    Edge u = std::make_pair(cur, ch);
    if(edges->find(u) == edges->end())
      return -1;
    cur = (*edges)[u];
    return cur;
  }

  DNF_STATE Goto(DNF_STATE i, char ch) {
    Edge u = std::make_pair(i, ch);
    if(edges->find(u) == edges->end())
      return -1;
    return (*edges)[u];
  }

  DNF_STATE state() { return cur; }

  bool Accepted(DNF_STATE i) {
    return acc->find(i) != acc->end();
  }

  bool Accepted() {
    return acc->find(cur) != acc->end();
  }

  int State_size() { return state_size; }
  const DNF_STATE Begin() { return start; }
  const std::set<char>* Alphabet() { return alphabet; }
  const Pos_set* Pos_sets(int i) {
    return (*pos_sets)[i];
  }
  const std::set<DNF_STATE>* Ends() {
    return acc;
  }
  

private:
  Ast *ast;
  
  int state_size;
  DNF_STATE start;
  std::vector<Pos_set*>* pos_sets;
  std::set<char>* alphabet;
  std::map<Edge, DNF_STATE>* edges;
  std::set<DNF_STATE>* acc;
  
  DNF_STATE cur;

private:

  void build_dfa(const std::vector<std::set<int>* >& followpos) {
    const int END_POS = ast->Leaf_size();
    std::unordered_map<Pos_set, DNF_STATE, Hash> mps;
    std::unordered_map<DNF_STATE, bool> vis;
    std::queue<DNF_STATE> Q;
    Q.push(start);
    mps[(*(*pos_sets)[0])] = start;
    // u -> v
    for(DNF_STATE u; !Q.empty(); ) {
      u = Q.front(); Q.pop();
      if(vis.find(u) != vis.end()) continue;
      vis[u] = true;
      if((*pos_sets)[u]->find(END_POS) != (*pos_sets)[u]->end())
        acc->insert(u);
      for(auto ch : (*alphabet)) {
        Pos_set *v = new Pos_set;
        for(auto p : (*(*pos_sets)[u])) {
          if(ast->Posch(p) == ch) {
            move_set2set(v, followpos[p]);
          }
        }
        if(v->empty()) { delete v; continue; }
        DNF_STATE t; // Get id of v
        if(mps.find(*v) == mps.end()) {
          t = mps[*v] = state_size++;
          pos_sets->push_back(v);
          Q.push(t);
        } else {
          t = mps[*v];
          delete v;
        }
        (*edges)[std::make_pair(u, ch)] = t;
      }
    }
  }

}; // class Automata

} // namespace lexer

#endif
