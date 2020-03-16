
#include <set>
#include <utility>

#ifndef _ITEM_H_
#define _ITEM_H_

namespace parser {

#define Kernel std::pair<int, int>
#define Item std::pair<Kernel, int>
#define NEW_ITEM(p, b, l) std::make_pair(std::make_pair(p, b), l)
#define Lok int
#define Core first
#define Lookahead second

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

  const int& Number() { return number; }
  const int Size() { return items.size(); }

  void Set_number(const int num) {
    number = num;
  }
  void Add_item(const Item& it) {
    items.insert(it);
    cores.insert(it.Core);
  }
  const std::set<Item>& Item_set() {
    return items;
  }
  const std::set<Kernel>& Cores() {
    return cores;
  }
  
  struct Core_cmp {
    bool operator()(
        const Items& items1,
        const Items& items2) {
      return items1.cores < items2.cores;
    }
  };

private:
  int number;
  std::set<Item> items;
  std::set<Kernel> cores;

}; // class Item

} // namespace parser

#endif
