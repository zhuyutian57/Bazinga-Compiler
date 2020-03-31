
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lexer/Terminal.h"
#include "../parser/ItemSet.h"
#include "../parser/Product.h"
#include "../symbol/UnitSet.h"

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace bin {

#define WIDTH 8
#define FORMAT std::cout.width(WIDTH), \
  std::cout.setf(std::ios::left)
#define PRINT_CHAR(n, fill_char) \
  for(int i = 0; i < n; i++) std::cout<< fill_char;

  
  inline void Print(const std::string& s) {
    std::cout << s << '\n';
  }

  inline void Error(const std::string& mes) { Print(mes); }

  // Wrong regular defination
  inline void ErrorRegularDefination(/*{{{*/
    const std::string& name,
    std::istringstream& ss) {
    std::cout<< name << " ->";
    std::string x;
    while(ss >> x) std::cout << " " + x;
    std::cout << " is not a regular defination\n";
  }/*}}}*/

  inline void PrintLabel(/*{{{*/
      const int& side_space,
      const std::string& label,
      const char& fill_char) {
    std::cout << '\n';
    PRINT_CHAR(side_space, fill_char);
    std::cout << ' ' << label << ' ';
    PRINT_CHAR(side_space, fill_char);
    std::cout << "\n\n";
  }/*}}}*/

  //TODO save informations in files
  void InfoAutomata(/*{{{*/
    int state_size,
    int start,
    const std::set<char>* alphabet,
    const std::set<int>* acc) {
    return;
    std::cout << "============= DFA =============\n";
    std::cout << " State size : "<< state_size << '\n';
    std::cout << " Start state : " << start << '\n';
    std::cout << " Alphabet : " << alphabet->size() << ' ';
    for(auto ch : (*alphabet))
      std::cout << ' ' << ch;    
    std::cout << '\n';
    std::cout << " Accepted states :";
    for(auto s : *acc) std::cout << ' ' << s;
    std::cout << '\n';
    std::cout << "============= DFA =============\n";
  }/*}}}*/

  void InfoLexer(/*{{{*/
    std::unordered_map<std::string, void*>* words,
    const std::vector<void*>* tokens) {
    return;
    std::cout << " Token stream : \n";
    std::string sym = ";+-*/=()";
    for(auto addr : (*tokens)) {
      Unit *t = (Unit*)addr;
      lexer::Terminal *p = (lexer::Terminal*)addr;
      std::cout << '<' << p->Tag() << ',';
      std::cout << '\t' << p->Lexeme() << ',';
      std::cout << '\t' << (*words)[p->Lexeme()] << ">\n";
    }
  }/*}}}*/

  void InfoProducts(/*{{{*/
      symbol::UnitSet& unitset,
      const std::vector<parser::Product*>& products) {
    const std::string label = "PRODUCTS";
    int side_space = 16;
    PrintLabel(side_space, label, '=');
    for(auto prod : products) {
      std::cout << "  " << prod->Number() << " . ";
      std::cout << unitset[prod->Head()] << " ->";
      for(int i = 0, j; j = prod->Body(i) ;i++) {
        if(j == -1) break;
        std::cout << ' ' << unitset[j];
      }
      std::cout << '\n';
    }
    PrintLabel(side_space, label, '=');
  }/*}}}*/

  void InfoFirstSets(/*{{{*/
      symbol::UnitSet& unitset,
      const std::unordered_map<int, std::set<int>*> first) {
    const std::string label = "FIRST SETS";
    int side_space = 16;
    PrintLabel(side_space, label, '=');
    for(auto f : first) {
      if(f.second->size() == 0) continue;
      std::cout << " - "<< unitset[f.first] << " :";
      for(auto tag : (*f.second))
        std::cout << ' ' << unitset[tag];
      std::cout << '\n';
    }
    PrintLabel(side_space, label, '=');
  }/*}}}*/

  void InfoItemSets(/*{{{*/
      symbol::UnitSet& unitset,
      const std::vector<parser::ItemSet*>& itemsets,
      const std::vector<std::vector<std::string> >& action_table) {
    const std::string label = "ITEMSETS";
    int side_space = 16;
    PrintLabel(side_space, label, '=');
    for(auto itemset : itemsets) {
      std::cout << " No." << itemset->Number();
      std::cout << " with " << itemset->Size() << " items\n";
      std::cout << " - Kernel Item:\n";
      for(auto item : itemset->Items()) {
        std::cout << " - " << item.PRODUCT_INDEX << ' '
          << item.DOT << " ,";
        for(auto lok : *itemset->LokSet(item))
          std::cout << ' ' << unitset[lok];
        std::cout << '\n';
      }
      std::cout << " - Shifts & Gotoes:\n";
      int state = itemset->Number();
      for(auto unit : unitset.Units()) {
        if(!unitset.IsIndexed(unit.Tag())) continue;
        int lo = unitset.Index(unit.Tag());
        if(action_table[state][lo] != "ERROR")
          std::cout << " - " << unitset[unit.Tag()] << ' '
            << action_table[state][lo] << '\n';
      }
      std::cout << '\n';
    }
    PrintLabel(side_space, label, '=');
  }/*}}}*/

  void InfoActionTable(/*{{{*/
      symbol::UnitSet& unitset,
      const std::vector<std::vector<std::string> >& action_table) {
    const std::string label = "ATION TABLE";
    int side_space = (unitset.Size() - 2) * WIDTH + 4;
    side_space -= label.size();
    side_space = (side_space + 1) / 2;
    PrintLabel(side_space, label, '=');
    FORMAT; std::cout << "State";
    for(auto unit : unitset.Units()) {
      if(unit.Tag() == symbol::Tag::EPSILON) continue;
      if(unit.Tag() == symbol::Tag::PROGRAM) continue;
      FORMAT; std::cout << unitset[unit.Tag()];
    }
    std::cout << '\n';
    int number = 0;
    for(auto actions : action_table) {
      FORMAT; std::cout << number++;
      for(auto action : actions) {
        FORMAT;
        if(action != "ERROR")
          std::cout << action;
        else std::cout << "-";
      }
      std::cout << '\n';
    }
    PrintLabel(side_space, label, '=');
  }/*}}}*/

  void InfoAction(/*{{{*/
    symbol::UnitSet& unitset,
    const std::unordered_map<int, std::set<int>*> first,
    const std::vector<parser::Product*>& products,
    const std::vector<parser::ItemSet*>& itemset,
    const std::vector<std::vector<std::string> >& action_table) {
    InfoProducts(unitset, products);
    InfoFirstSets(unitset, first);
    InfoItemSets(unitset, itemset, action_table);
    InfoActionTable(unitset, action_table);
  }/*}}}*/

} // namespace message

#endif
