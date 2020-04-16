
#include "Bin.h"
#include "Graph.h"
#include "ItemSet.h"
#include "Product.h"
#include "UnitSet.h"

using namespace bin;
using namespace symbols;

#ifndef _ACTION_H_
#define _ACTION_H_

namespace parser {

class Action {

public:
  Action() {}
  ~Action() {}

  bool Build(const char*);
  const std::string& ACTION(const ACTION_STATE&, const LOK&);
  Product* GetProduct(const int&);
  UnitSet& Units();

private:
  UnitSet unitset;
  std::unordered_map<int, std::set<int>* > first;
  std::vector<Product*> products;
  std::vector<ItemSet*> itemsets;
  std::vector<ACTION_SET> action_table;

private:
  bool GenerateActionTable(const char*);
  bool RecognizeCFL(const char*);
  void CalculateFirstTerminalOfUnit();  
  void AddItemSet(ItemSet*);
  void BuildLokSet();
  ItemSet* LRZeroClosure(const ItemSet*);
  ItemSet* LRZeroGoto(ItemSet*, const Unit&);
  bool GenerateShiftAndGoto(ItemSet*, Unit&, ItemSet*);
  void GetEpsilonItems(ItemSet*);
  bool GenerateLRZeroItemSet();
  LOKSET* FirstBetaA(const std::vector<LOK>&, const LOK&);
  LOKSET* FirstBetaA(const LRONE_ITEM&);
  LRONE_ITEMSET* LROneClosure(const ITEM&);
  int LROneGoto(const int&, const int&);
  Graph* DetermineLookahead();
  bool GenerateLALROneItemSet();
  bool GetAllBodies(const ITEM&);
  bool GenerateReduce();

  void InformationOfProducts();
  void InformationOfFirstSets();
  void InformationOfItemSets();
  void InformationOfActionTable();
  void Informations();

}; // class Action

}; // namespace parser

#endif
