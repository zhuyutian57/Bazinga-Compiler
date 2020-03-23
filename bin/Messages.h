
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lexer/Terminal.h"
#include "../parser/Itemset.h"
#include "../parser/Product.h"
#include "../symbol/Unitset.h"

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace bin {

  inline void error(const std::string& mes) {/*{{{*/
    std:: cout << mes << '\n';
  }/*}}}*/

  // Wrong regular defination
  inline void err_rd(/*{{{*/
    const std::string& name,
    std::istringstream& ss) {
    std::cout<< name << " ->";
    std::string x;
    while(ss >> x) std::cout << " " + x;
    std::cout << " is not a regular defination\n";
  }/*}}}*/

  //TODO save informations in files
  void info_automata(/*{{{*/
    int state_size,
    int start,
    const std::set<char>* alphabet,
    const std::set<int>* acc) {
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

  void info_lexer(/*{{{*/
    std::unordered_map<std::string, void*>* words,
    const std::vector<void*>* tokens) {
    std::cout << " Token stream : \n";
    std::string sym = ";+-*/=()";
    for(auto addr : (*tokens)) {
      Unit *t = (Unit*)addr;
      lexer::Terminal *p = (lexer::Terminal*)addr;
      std::cout << '<' << p->Tag() << ',';
      std::cout << '\t' << p->Lexe() << ',';
      std::cout << '\t' << (*words)[p->Lexe()] << ">\n";
    }
  }/*}}}*/

  void info_action(/*{{{*/
    const std::unordered_map<int, std::set<int>*> first,
    const std::vector<parser::Product*>& products,
    const std::vector<parser::Itemset*>& itemset,
    const std::vector<std::vector<std::string> >& actions) {
    symbol::Unitset *units = new Unitset();
    std::cout << " ============= ACTIONS =============\n";
    std::cout << " Products :\n";
    for(auto prod : products) {
      std::cout << "    " << prod->Number() << " : ";
      std::cout << (*units)[prod->Head()] << " ->";
      for(int i = 0, j; j = prod->Body(i) ;i++) {
        if(j == -1) break;
        std::cout << ' ' << (*units)[j];
      }
      std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << " - FIRST set:\n";
    for(auto f : first) {
      if(f.second->size() == 0) continue;
      std::cout << " - "<< (*units)[f.first] << " :";
      for(auto tag : (*f.second))
        std::cout << ' ' << (*units)[tag];
      std::cout << '\n';
    }
    std::cout << '\n';
    for(auto items : itemset) {
      std::cout << " - Itemset " << items->Number();
      std::cout << " - " << items->Size() << " item-s\n";
      std::cout << " - kernel item:\n";
      for(auto item : items->Items()) {
        std::cout << " - "
          << item.Core.first << ' '
          << item.Core.second << " , "
          << (*units)[item.Lookahead];
        std::cout << '\n';
      }
      std::cout << " - actions & gotoes:\n";
      int state = items->Number();
      for(auto unit : units->Units()) {
        int lo = units->Loc(unit.Tag());
        if(actions[state][lo] != "ERROR")
          std::cout << " - " << (*units)[unit.Tag()] << ' '
            << actions[state][lo] << '\n';
      }
      std::cout << '\n';
    }
    std::cout << " ============= ACTIONS =============\n";
  }/*}}}*/

} // namespace message

#endif
