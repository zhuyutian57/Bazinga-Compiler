
#include "Bin.h"

using namespace bin;

#ifndef _ITEMSET_H_
#define _ITEMSET_H_

namespace parser {

class ItemSet {

public:
  ItemSet() {}
  ItemSet(const ITEM&, const int);
  ItemSet(const ItemSet*);
  ~ItemSet();

  bool operator==(const ItemSet&) const;
  bool operator<(const ItemSet& it) const;

  void SetNumber(const int);
  void AddItem(const ITEM&);
  const int& Number();
  const int Size();
  ITEMSET& Items(); 
  LOKSET* LokSet(const ITEM& it);
  void BuildLokSet();

private:
  int              number;
  ITEMSET          items;
  ITEM_TO_LOKSET   item_to_lokset;

}; // class ItemSet

} // namespace parser

#endif
