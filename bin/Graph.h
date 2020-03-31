
#include <set>
#include <unordered_map>
#include <vector>

#ifndef _GRAPH_H_
#define _GRAPH_H_

namespace bin {

#define VALTYPE         std::set<int>*
#define NODESET         std::vector<VALTYPE>
#define EDGESET_OF_NODE std::vector<VALTYPE>
#define EDGESET         std::vector<EDGESET_OF_NODE>
  

class Graph {

public:
  Graph() { edges.clear(); }
  ~Graph() {}

  void AddNode(VALTYPE val) {
    if(index.find(val) != index.end()) return;
    index[val] = edges.size();
    nodes.push_back(val);
    edges.push_back(std::vector<VALTYPE>());
  }
  void AddEdge(VALTYPE from, VALTYPE to) {
    AddNode(from); AddNode(to);
    edges[index[from]].push_back(to);
  }
  const NODESET& Nodes() { return nodes; }
  const EDGESET_OF_NODE& EdgesOfNode(VALTYPE val) {
    return edges[index[val]];
  }

private:
  NODESET nodes;
  EDGESET edges;
  std::unordered_map<VALTYPE, int> index;

}; // class Graph

} // namespace bin

#endif
