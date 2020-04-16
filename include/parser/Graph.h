
#include "Bin.h"
#include "Stl.h"

#ifndef _GRAPH_H_
#define _GRAPH_H_

namespace parser {

class Graph {

public:
  Graph();
  ~Graph() {}

  void AddNode(VALTYPE);
  void AddEdge(VALTYPE, VALTYPE);
  const NODESET& Nodes();
  const EDGESET_OF_NODE& EdgesOfNode(VALTYPE);

private:
  NODESET nodes;
  EDGESET edges;
  std::unordered_map<VALTYPE, int> index;

}; // class Graph

} // namespace parser

#endif
