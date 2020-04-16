
#include "ItemSet.h"

using namespace parser;
  
ItemSet::ItemSet(const ITEM& item, const int num) {
  items.insert(item);
  number = num;
}
ItemSet::ItemSet(const ItemSet* itemset) {
  number = itemset->number;
  items = itemset->items;
}
ItemSet::~ItemSet() {
  for(auto pair : item_to_lokset)
    delete pair.second;
}

bool ItemSet::operator==(const ItemSet& it) const {
  return items == it.items;
}
bool ItemSet::operator<(const ItemSet& it) const {
  return items < it.items;
}

void ItemSet::SetNumber(const int num) { number = num; }
void ItemSet::AddItem(const ITEM& it) { items.insert(it); }
const int& ItemSet::Number() { return number; }
const int ItemSet::Size() { return items.size(); }
ITEMSET& ItemSet::Items() { return items; } 
LOKSET* ItemSet::LokSet(const ITEM& it) {
  return item_to_lokset[it];
}
void ItemSet::BuildLokSet() {
  for(auto item : items)
    item_to_lokset[item] = new LOKSET;
}
