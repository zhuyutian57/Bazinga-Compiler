
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
#define PRODUCT_ID Core.first
#define DOT Core.second

class Itemset {

public:
  Itemset() { cores = new std::set<Kernel>; }
  ~Itemset() {}
  bool operator==(const Itemset& it) const {
    return items == it.items;
  }
  bool operator<(const Itemset& it) const {
    return items < it.items;
  }

  void Set_number(const int num) {
    number = num;
  }

  void Add_item(const Item& it) {
    items.insert(it);
    cores->insert(it.Core);
  }

  auto Erase(auto it) { return items.erase(it); }

  const int& Number() { return number; }
  const int Size() { return items.size(); }
  const std::set<Item>& Items() {
    return items;
  }
  const std::set<Kernel>* Cores() {
    return cores;
  }
  
  struct Core_cmp {
    bool operator()(const Itemset& it1,
        const Itemset& it2) {
      return (*it1.cores) < (*it2.cores);
    }
  };

private:
  int number;
  std::set<Item> items;
  std::set<Kernel>* cores;

}; // class Itemset

} // namespace parser

#endif
