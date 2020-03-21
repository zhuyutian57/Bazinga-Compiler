
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
#include "Itemset.h"
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

#define STATE int
#define ACTION_ERROR "ERROR"
#define ACTION_SET std::vector<std::string>
#define NEW_ACTION ACTION_SET( \
    units_ptr->Units_size() - 2, ACTION_ERROR)

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
    info_action(first, products, itemsets, actions);
    return true;
  }/*}}}*/

  const inline std::string& ACTION(
      const STATE& s, const Lok& lok) {
    return actions[s][units_ptr->Loc(lok)];
  }

  //Test
  Units* Units_ptr() { return units_ptr; }
  std::vector<ACTION_SET>& Actions() {
    return actions;
  }

private:
  Units* units_ptr;
  std::unordered_map<int, std::set<int>* > first;
  std::vector<Product*> products;
  std::vector<Itemset*> itemsets;  
  // ACTIONs and GOTOs
  std::vector<ACTION_SET> actions;

private:

  bool gen_action(const char* grammars) {/*{{{*/
    if(!recognize_cfg(grammars)) return false;
    FIRST_of_units();
    if(!gen_LR1_itemsets()) return false;
    remove_nonkernel_item();
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
    int h = it.PRODUCT_ID;
    int b = it.DOT + 1;
    while(products[h]->Body(b) != -1)
      beta.push_back(products[h]->Body(b++));
    return FIRST(beta, it.Lookahead);
  }/*}}}*/

  // Run bfs to get closure of a kernel itemset
  Itemset* CLOSURE(Itemset* kernel_itemset) {/*{{{*/
    Itemset *its = new Itemset();
    its->Set_number(kernel_itemset->Number());
    std::map<Item, bool> vis; // Visited or not
    std::queue<Item> Q;
    for(auto item : kernel_itemset->Items())
      Q.push(item);
    while(!Q.empty()) {
      Item it = Q.front(); Q.pop();
      if(vis[it]) continue;
      vis[it] = true;
      its->Add_item(it);
      int head = products[it.PRODUCT_ID]->Body(it.DOT);
      if(head < NONTERMINAL_BEGIN) continue;
      std::set<int>* loks = FIRST(it);
      for(auto prod : products)
        if(prod->Head() == head)
          for(auto lo : *loks)
            Q.push(NEW_ITEM(prod->Number(), 0, lo));
      delete loks;
    }
    return its;
  }/*}}}*/

  Itemset* GOTO(Itemset *I, Unit& unit) {/*{{{*/
    Itemset *new_kernel_itemset = new Itemset();
    for(auto item : I->Items()) {
      int h = item.PRODUCT_ID;
      int b = item.DOT;
      if(products[h]->Body(b) != unit.Tag())
        continue;
      new_kernel_itemset->Add_item(
          NEW_ITEM(h, b + 1, item.Lookahead));
    }
    Itemset *result = NULL;
    if(new_kernel_itemset->Size() != 0)
      result = CLOSURE(new_kernel_itemset);
    delete new_kernel_itemset;
    return result;
  }/*}}}*/

  inline bool placed(const STATE& i, const Lok& lok) {/*{{{*/
    return actions[i][lok] != ACTION_ERROR;
  }/*}}}*/

  inline bool gen_shift_and_goto(/*{{{*/
      const STATE& out,
      const int& unit_tag,
      const STATE& in) {
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

  void init_item_zero() {/*{{{*/
    Itemset *beg = new Itemset();
    beg->Add_item(NEW_ITEM(0, 0, '$'));
    beg->Set_number(itemsets.size());
    actions.push_back(NEW_ACTION);
    itemsets.push_back(CLOSURE(beg));
    delete beg;
  }/*}}}*/

  // Run bfs to calculate itemsets
  // Extra: calculating shift-actions and GOTOs
  bool gen_LR1_itemsets() {/*{{{*/
    init_item_zero();
    std::map<Itemset, STATE, Itemset::Core_cmp> number;
    std::queue<Itemset*> Q;
    Q.push(itemsets[0]);
    number[(*Q.front())] = 0;
    while(!Q.empty()) {
      Itemset *I = Q.front(); Q.pop();
      for(auto unit : units_ptr->Unitset()) {
        if(unit.Tag() == Tag::PROGRAM ||
            unit.Tag() == Tag::EPSILON)
          continue;
        Itemset *new_itemset = GOTO(I, unit);
        if(new_itemset == NULL) continue;
        int n_state; // GOTO(I, Unit) = n_state
        if(number.find(*new_itemset) == number.end()) {
          n_state = number[*new_itemset] = itemsets.size();
          new_itemset->Set_number(n_state);
          itemsets.push_back(new_itemset);
          actions.push_back(NEW_ACTION);
          Q.push(new_itemset);
        } else {
          n_state = number[*new_itemset];
          delete new_itemset;
        }
        if(!gen_shift_and_goto(I->Number(), unit.Tag(), n_state))
          return false;
      }
    }
    return true;
  }/*}}}*/

  inline bool reduce_item(const Kernel& core) {/*{{{*/
    const int b = products[core.first]->Body(core.second);
    return b == -1 || b == Tag::EPSILON;
  }/*}}}*/

  inline void remove_nonkernel_item() {/*{{{*/
    for(auto its : itemsets) {
      for(auto it = its->Items().begin();
          it != its->Items().end();) {
        const int& p_id = (*it).PRODUCT_ID;
        const int& dot = (*it).DOT;
        if(dot != 0 || p_id == 0 ||
            products[p_id]->Body(dot) == Tag::EPSILON) {
          it++; continue;
        }
        it = its->Erase(it);
      }
    }
  }/*}}}*/

  bool gen_reduce_actions() {/*{{{*/
    for(auto I : itemsets) {
      const int& i = I->Number();
      for(auto it : I->Items()) {
        if(!reduce_item(it.Core)) continue;
        if(placed(i, units_ptr->Loc(it.Lookahead))) {
          error("Reduce conflict :" + std::to_string(i)
              + " - " + (*units_ptr)[it.Lookahead]);
          return false;
        }
        std::string ac;
        if(it.PRODUCT_ID == 0) ac = "ACC";
        else ac = "R" + std::to_string(it.PRODUCT_ID);
        actions[i][units_ptr->Loc(it.Lookahead)] = ac;
      }
    }
    return true;
  }/*}}}*/

}; // class Action

}; // namespace parser

#endif
