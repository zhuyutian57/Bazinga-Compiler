
#include <set>
#include <utility>

#ifndef _ITEM_H_
#define _ITEM_H_

namespace parser {

#define Item std::pair<int, int>
#define New_item(a,b) std::make_pair(a,b)

class Items {

public:
  Items(){}
  ~Items(){}
  bool operator==(const Items& it) const {
    return items == it.items;
  }
  bool operator<(const Items& it) const {
    return items < it.items;
  }

  int Number() { return number; }
  const int Size() { return items.size(); }

  void Set_number(const int num) {
    number = num;
  }
  void Add_item(Item it) {
    items.insert(it);
  }
  const std::set<Item>& Item_set() {
    return items;
  }

private:
  int number;
  std::set<Item> items;

}; // class Item


} // namespace parser

#endif
