
#include <map>
#include <set>
#include <utility>
#include <vector>

#ifndef _ITEMSET_H_
#define _ITEMSET_H_

namespace parser {

//LR0 item
#define ITEM            std::pair<int, int>
#define NEW_ITEM(product_index, dot) \
  std::make_pair(product_index, dot)
#define ITEMSET         std::set<ITEM>
#define LOK             int
#define LOKSET          std::set<LOK>
#define ITEM_TO_LOKSET  std::map<ITEM, LOKSET*>
#define PRODUCT_INDEX   first
#define DOT             second

class ItemSet {

public:
  ItemSet() {}
  ItemSet(const ITEM& item, const int num) {
    items.insert(item);
    number = num;
  }
  ItemSet(const ItemSet* itemset) {
    number = itemset->number;
    items = itemset->items;
  }
  ~ItemSet() {
    for(auto pair : item_to_lokset)
      delete pair.second;
  }

  bool operator==(const ItemSet& it) const {
    return items == it.items;
  }
  bool operator<(const ItemSet& it) const {
    return items < it.items;
  }

  void SetNumber(const int num) { number = num; }
  void AddItem(const ITEM& it) { items.insert(it); }
  const int& Number() { return number; }
  const int Size() { return items.size(); }
  ITEMSET& Items() { return items; } 
  LOKSET* LokSet(const ITEM& it) {
    return item_to_lokset[it];
  }
  inline void BuildLokSet() {
    for(auto item : items)
      item_to_lokset[item] = new LOKSET;
  }

private:
  int              number;
  ITEMSET          items;
  ITEM_TO_LOKSET   item_to_lokset;

}; // class ItemSet

} // namespace parser

#endif
