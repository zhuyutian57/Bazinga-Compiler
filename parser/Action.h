
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

#include "../bin/Funtions.h"
#include "../bin/Messages.h"
using namespace bin;

#ifndef _ACTION_H_
#define _ACTION_H_

namespace parser {

#define State int
#define ACTION std::string
#define INPUT int
#define NONTERMINAL int
#define STATE_INPUT std::pair<State, INPUT>
#define NEW_INPUT(s, i) std::make_pair(s, i)
#define NONTERMINAL_BEGIN 401

class Action {

public:
  Action() {/*{{{*/
    // Terminals
    reserve("TYPE", Tag::TYPE);
    reserve("ID", Tag::ID);
    reserve("INTEGER", Tag::INTEGER);
    reserve("FLOAT", Tag::FLOAT);
    reserve('+'); reserve('-');
    reserve('*'); reserve('/');
    reserve(';'); reserve('=');
    reserve('('); reserve(')');
    // Nonterminals
    reserve("Epsilon", Tag::EPSILON);
    reserve("Program", Tag::PROGRAM);
    reserve("Stmts", Tag::STMTS);
    reserve("Stmt", Tag::STMT);
    reserve("Expr", Tag::EXPR);
    reserve("Term", Tag::TERM);
    reserve("Unary", Tag::UNARY);
    reserve("Factor", Tag::FACTOR);
    reserve("ADD_ID", Tag::ADD_ID);
    reserve("ID_EXIST", Tag::ID_EXIST);
    // Test
    reserve("P", Tag::P);
    reserve("S", Tag::S);
    reserve("L", Tag::L);
    reserve("R", Tag::R);
  }/*}}}*/
  ~Action() {}

  bool Build(const char* grammars) {/*{{{*/
    if(!gen_action(grammars)) return false;
    /*info_action(
        unit_tags, units, products,
        items_set, actions, gotoes
        );*/
    return true;
  }/*}}}*/

private:
  std::unordered_map<std::string, int> unit_tags;
  std::set<Unit> units; // Units
  std::unordered_map<int, std::set<int>* > first;
  std::vector<Product*> products;
  std::vector<Items*> items_set;  
  // Two main tables
  std::map<STATE_INPUT, ACTION> actions;
  std::map<STATE_INPUT, State> gotoes;

private:
  void reserve(const char ch) {/*{{{*/
    units.insert(Unit(ch));
    unit_tags[std::string("") + ch] = ch;
  }

  void reserve(const std::string& s, int t) {
    if(t != Tag::PROGRAM)
      units.insert(Unit(t));
    unit_tags[s] = t;
  }/*}}}*/

  int unit_tag(std::string& name) {/*{{{*/
    return unit_tags[name];
  }/*}}}*/

  bool gen_action(const char* grammars) {/*{{{*/
    if(!recognize_cfg(grammars)) return false;
    cal_FIRST();
    return true;
    if(!gen_LR0_kernel_items()) return false;
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
      prod->Set_head(unit_tag(word));
      ss >> word;
      if(word != "->") return false;
      while(ss >> word)
        prod->Add_body(unit_tag(word));
      prod->Set_number(products.size());
      products.push_back(prod);
    }
    return true;
  }/*}}}*/

  //TODO test
  void cal_FIRST() {/*{{{*/
    for(auto unit : units) {
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
          int head_first_size = first[h]->size();
          move_set2set(first[h], first[b]);
          if(first[h]->size() != head_first_size)
            has_move = true;
        }
      }
    }
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
        = products[it.Core().first]
          ->Body(it.Core().second);
      if(head < NONTERMINAL_BEGIN) continue;
      //(TODO) calculate FIRST
      //for(auto prod : products)
      //  if(prod->Head() == head)
      //    Q.push(New_item(prod->Number(), 0));
    }
    return items;
  }/*}}}*/

  Items* GOTO(Items *I, Unit& unit) {/*{{{*/
    Items *new_items = new Items();
    for(auto item : I->Item_set()) {
      int h = item.Core().first;
      int p = item.Core().second;
      if(products[h]->Body(p) != unit.Tag())
        continue;
      new_items->Add_item(
          Item(std::make_pair(h, p + 1),
            item.Lookaheads()));
    }
    if(new_items->Size() == 0) {
      delete new_items;
      return NULL;
    }
    return new_items;
  }/*}}}*/

  // Including the calculationg of
  // shift-actions and GOTO-table
  bool gen_LR0_kernel_items() {/*{{{*/
    Items *beg = new Items();
    Item it = Item(std::make_pair(0, 0));
    it.Add_lookahead('$');
    beg->Add_item(it);
    beg->Set_number(items_set.size());
    items_set.push_back(beg);

    std::map<Items, int> id;
    std::queue<Items*> Q;
    id[*beg] = 0; Q.push(beg);
    while(!Q.empty()) {
      Items *I = Q.front(); Q.pop();
      I = CLOSURE(I);
      for(auto unit : units) {
        Items *new_items = GOTO(I, unit);
        if(new_items == NULL) continue;
        int n_state; // GOTO(I, Unit) = n_state
        if(id.find(*new_items) == id.end()) {
          n_state = id[*new_items] = items_set.size();
          new_items->Set_number(n_state);
          items_set.push_back(new_items);
          Q.push(new_items);
        } else {
          n_state = id[*new_items];
          delete new_items;
        }
        // Generate shift-actions and GOTO-table
        STATE_INPUT n_state_input
          = NEW_INPUT(I->Number(), unit.Tag()); 
        if(unit.Tag() < NONTERMINAL_BEGIN) {
          actions[n_state_input]
            = std::string("S") + std::to_string(n_state);
        } else {
          gotoes[n_state_input] = n_state;
        }
      }
    }
    return true;
  }/*}}}*/

}; // class Action

}; // namespace parser

#endif
