
#include <set>
#include <utility>

#ifndef _ITEM_H_
#define _ITEM_H_

namespace parser {

class Item {

public:
  Item(){}
  Item(const std::pair<int, int>& c) { core = c; }
  Item(const std::pair<int, int>& c,
      const std::set<int>& loks) {
    core = c;
    lookaheads = loks;
  }
  ~Item(){}
  bool operator==(const Item& it) const {
    return core == it.core;
  }
  bool operator<(const Item& it) const {
    return core < it.core;
  }

  void Set_core(const std::pair<int, int>& c) {
    core = c;
  }
  void Add_lookahead(const int& lok) {
    lookaheads.insert(lok);
  }

  const std::pair<int, int>& Core() { return core; }
  const std::set<int>& Lookaheads() { return lookaheads; }

private:
  std::pair<int, int> core;
  std::set<int> lookaheads;

}; // class Item

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
  void Add_item(const Item& it) {
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
