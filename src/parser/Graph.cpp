
#include "Graph.h"

using namespace parser;

Graph::Graph() { edges.clear(); }

void Graph::AddNode(VALTYPE val) {
  if(index.find(val) != index.end()) return;
  index[val] = edges.size();
  nodes.push_back(val);
  edges.push_back(std::vector<VALTYPE>());
}

void Graph::AddEdge(VALTYPE from, VALTYPE to) {
  AddNode(from); AddNode(to);
  edges[index[from]].push_back(to);
}

const NODESET& Graph::Nodes() { return nodes; }

const EDGESET_OF_NODE& Graph::EdgesOfNode(VALTYPE val) {
  return edges[index[val]];
}
