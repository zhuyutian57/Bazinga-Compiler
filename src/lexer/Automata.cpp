
#include "Automata.h"

using namespace bin;
using namespace lexer;

Automata::Automata() { ast = new Ast; }

Automata::~Automata() { delete ast; }

void Automata::Build(const char* rd_path) {
  ast->Build(rd_path);
  MoveSetToSet(&ast->Characters(), &alphabet);
  ast_leaf_sets.push_back(new AST_LEAVES_SET);
  MoveSetToSet(&ast->RootFirstpos(), ast_leaf_sets[0]);
  start = 0;
  state_size = 1;
  BuildDFA(ast->Followpos());
  Print("Automata is ok!");
  Informations();
}

void Automata::Reset() { current_state = start; }

DNF_STATE Automata::Goto(char ch) {
  DFA_EDGE u = std::make_pair(current_state, ch);
  if(edges.find(u) == edges.end())
    return -1;
  current_state = edges[u];
  return current_state;
}
bool Automata::Accepted() {
  return accepted_states.find(current_state)
    != accepted_states.end();
}

void Automata::BuildDFA(const std::vector<std::set<int>*>& followpos) {
  const int END_POS = ast->LeafSize();
  std::unordered_map<AST_LEAVES_SET, DNF_STATE, Hash> mps;
  std::unordered_map<DNF_STATE, bool> vis;
  std::queue<DNF_STATE> Q;
  Q.push(start);
  mps[(*ast_leaf_sets[0])] = start;
  for(DNF_STATE u; !Q.empty(); ) {
    u = Q.front(); Q.pop();
    if(vis.find(u) != vis.end()) continue;
    vis[u] = true;
    if(ast_leaf_sets[u]->find(END_POS) != ast_leaf_sets[u]->end())
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
}

void Automata::Informations() {
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
}
