
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Expr.h"
#include "Factor.h"
#include "Items.h"
#include "Product.h"
#include "Stmt.h"
#include "Stmts.h"
#include "Term.h"
#include "Unary.h"
#include "Units.h"

#include "../bin/Funtions.h"
#include "../bin/Messages.h"
using namespace bin;

#ifndef _ACTION_H_
#define _ACTION_H_

namespace parser {

#define State int
#define ACTION_ERROR "ERROR"
#define ACTION std::vector<std::string>
#define NEW_ACTION ACTION(units_ptr->Units_size(), ACTION_ERROR)

class Action {

public:
  Action() {/*{{{*/
    units_ptr = new Units();
  }
  ~Action() {
    delete units_ptr;
  }/*}}}*/

  bool Build(const char* grammars) {/*{{{*/
    if(!gen_action(grammars)) return false;
    info_action(first, products, items_set, actions);
    return true;
  }/*}}}*/

private:
  Units* units_ptr;
  std::unordered_map<int, std::set<int>* > first;
  std::vector<Product*> products;
  std::vector<Items*> items_set;  
  // ACTIONs and GOTOs
  std::vector<ACTION> actions;

private:

  bool gen_action(const char* grammars) {/*{{{*/
    if(!recognize_cfg(grammars)) return false;
    FIRST_of_units();
    if(!gen_LALR1_kernel_items()) return false;
    if(!gen_reduce_actions()) return false;
    return true;
  }/*}}}*/

  bool recognize_cfg(const char* grammars) {/*{{{*/
    freopen(grammars, "r", stdin);
    std::string product;
    while(std::getline(std::cin, product)) {
      // make product as word stream
      // head -> body1 body2 ...
      std::istringstream ss(product);
      Product *prod = new Product();
      std::string word;
      ss >> word;
      prod->Set_head((*units_ptr)[word]);
      ss >> word;
      if(word != "->") return false;
      while(ss >> word)
        prod->Add_body((*units_ptr)[word]);
      prod->Set_number(products.size());
      products.push_back(prod);
    }
    return true;
  }/*}}}*/

  void FIRST_of_units() {/*{{{*/
    for(auto unit : units_ptr->Unitset()) {
      int t = unit.Tag();
      first[t] = new std::set<int>;
      if(t < NONTERMINAL_BEGIN)
        first[t]->insert(t);
    }
    for(bool has_move = true; has_move; ) {
      has_move = false;
      for(auto prod : products) {
        int h = prod->Head();
        for(int i = 0, b; ; i++) {
          b = prod->Body(i);
          if(b == -1) break;
          int head_first_size = first[h]->size();
          move_set2set(first[h], first[b]);
          if(first[h]->size() != head_first_size)
            has_move = true;
          if(first[b]->find(Tag::EPSILON)
              == first[b]->end())
            break;
        }
      }
    }
  }/*}}}*/

  // Calculate FIRST(βa)
  std::set<Lok>* FIRST(/*{{{*/
      const std::vector<Lok>& beta,
      const Lok& a) {
    std::set<Lok>* loks = new std::set<Lok>;
    bool eps = true;
    for(auto unit : beta) {
      for(auto u : (*first[unit]))
        if(u != Tag::EPSILON)
          loks->insert(u);
      if(first[unit]->find(Tag::EPSILON)
          == first[unit]->end()) {
        eps = false; break;
      }
    }
    if(eps) loks->insert(a);
    return loks;
  }
  std::set<Lok>* FIRST(Item& it) {
    std::vector<Lok> beta;
    int h = it.Core.first;
    int b = it.Core.second + 1;
    while(products[h]->Body(b) != -1)
      beta.push_back(products[h]->Body(b++));
    return FIRST(beta, it.Lookahead);
  }/*}}}*/

  // Run bfs to get closure of a kernel items set
  Items* CLOSURE(Items* kernel_items) {/*{{{*/
    Items *items = new Items();
    items->Set_number(kernel_items->Number());
    std::map<Item, bool> vis; // Visited or not
    std::queue<Item> Q;
    for(auto item : kernel_items->Item_set())
      Q.push(item);
    while(!Q.empty()) {
      Item it = Q.front(); Q.pop();
      if(vis[it]) continue;
      vis[it] = true;
      items->Add_item(it);
      int head
        = products[it.Core.first]
          ->Body(it.Core.second);
      if(head < NONTERMINAL_BEGIN) continue;
      std::set<int>* loks = FIRST(it);
      for(auto prod : products)
        if(prod->Head() == head)
          for(auto lo : *loks)
            Q.push(NEW_ITEM(prod->Number(), 0, lo));
      delete loks;
    }
    return items;
  }/*}}}*/

  Items* GOTO(Items *I, Unit& unit) {/*{{{*/
    Items *new_items = new Items();
    for(auto item : I->Item_set()) {
      int h = item.Core.first;
      int b = item.Core.second;
      if(products[h]->Body(b) != unit.Tag())
        continue;
      new_items->Add_item(NEW_ITEM(h, b + 1,
            item.Lookahead));
    }
    if(new_items->Size() == 0) {
      delete new_items;
      return NULL;
    }
    return new_items;
  }/*}}}*/

  inline bool placed(const State& i, const Lok& lok) {/*{{{*/
    return actions[i][lok] != ACTION_ERROR;
  }/*}}}*/

  inline bool gen_shift_and_goto(/*{{{*/
      const State& out,
      const int& unit_tag,
      const State& in) {
    int lok = units_ptr->Loc(unit_tag);
    if(placed(out, lok)) {
      error("Shift conflict : " + std::to_string(out)
          + " - " + (*units_ptr)[unit_tag]);
      return false;
    }
    std::string act = "";
    if(unit_tag < NONTERMINAL_BEGIN) act = "S";
    actions[out][lok] = act + std::to_string(in);
    return true;
  }/*}}}*/

  // Including the calculationg of
  // shift-actions and GOTO-table
  bool gen_LALR1_kernel_items() {/*{{{*/
    Items *beg = new Items();
    beg->Add_item(std::make_pair(
          std::make_pair(0, 0), '$'));
    beg->Set_number(items_set.size());
    actions.push_back(NEW_ACTION);
    items_set.push_back(beg);
    // Run bfs to calculate items
    std::map<Items, State, Items::Core_cmp> number;
    std::queue<Items*> Q;
    number[*beg] = 0; Q.push(beg);
    while(!Q.empty()) {
      Items *I = Q.front(); Q.pop();
      I = CLOSURE(I);
      for(auto unit : units_ptr->Unitset()) {
        Items *new_items = GOTO(I, unit);
        if(new_items == NULL) continue;
        int n_state; // GOTO(I, Unit) = n_state
        if(number.find(*new_items) == number.end()) {
          n_state = number[*new_items] = items_set.size();
          new_items->Set_number(n_state);
          items_set.push_back(new_items);
          actions.push_back(NEW_ACTION);
          Q.push(new_items);
        } else {
          n_state = number[*new_items];
          delete new_items;
        }
        if(!gen_shift_and_goto(I->Number(), unit.Tag(), n_state))
          return false;
      }
    }
    return true;
  }/*}}}*/

  inline bool reduce_item(const Kernel& core) {/*{{{*/
    return products[core.first]->Body(core.second) == -1;
  }/*}}}*/

  bool gen_reduce_actions() {/*{{{*/
    for(auto I : items_set) {
      const int& i = I->Number();
      for(auto it : I->Item_set()) {
        if(!reduce_item(it.Core)) continue;
        if(placed(i, units_ptr->Loc(it.Lookahead))) {
          error("Reduce conflict :" + std::to_string(i)
              + " - " + (*units_ptr)[it.Lookahead]);
          return false;
        }
        actions[i][units_ptr->Loc(it.Lookahead)] =
          "R" + std::to_string(it.Core.first);
      }
    }
    return true;
  }/*}}}*/

}; // class Action

}; // namespace parser

#endif
