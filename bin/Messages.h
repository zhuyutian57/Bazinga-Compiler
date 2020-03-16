
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lexer/Word.h"
#include "../parser/Items.h"
#include "../parser/Product.h"
#include "../parser/Units.h"

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
      // Check weather *t is a word
      bool flag = false;
      for(auto ch : sym)
        if(ch == t->Tag())
          flag = true;
      if(!flag) {
        lexer::Word *p = (lexer::Word*)addr;
        std::cout << '<' << p->Tag() << ',';
        std::cout << p->Lexe() << ',';
        std::cout << (*words)[p->Lexe()] << ">\n";
      } else {
        std::cout << '<' << char(t->Tag()) << ',';
        std::cout << (*words)[std::string(1, t->Tag())]
                  << ">\n";
      }
    }
  }/*}}}*/

  void info_action(
    const std::unordered_map<int, std::set<int>*> first,
    const std::vector<parser::Product*>& products,
    const std::vector<parser::Items*>& items_set,
    const std::vector<std::vector<std::string> >& actions) {
    parser::Units mp;
    std::cout << " ============= ACTIONS =============\n";
    std::cout << " Products :\n";
    for(auto prod : products) {
      std::cout << "    " << prod->Number() << " : ";
      std::cout << mp[prod->Head()] << " ->";
      for(int i = 0, j; j = prod->Body(i) ;i++) {
        if(j == -1) break;
        std::cout << ' ' << mp[j];
      }
      std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << " - FIRST set:\n";
    for(auto f : first) {
      if(f.second->size() == 0) continue;
      std::cout << " - "<< mp[f.first] << " :";
      for(auto tag : (*f.second))
        std::cout << ' ' << mp[tag];
      std::cout << '\n';
    }
    std::cout << '\n';
    for(auto items : items_set) {
      std::cout << " - Items " << items->Number();
      std::cout << " - " << items->Size() << " item-s\n";
      std::cout << " - kernel item:\n";
      for(auto item : items->Item_set()) {
        std::cout << " - "
          << item.Core.first << ' '
          << item.Core.second << " , "
          << mp[item.Lookahead];
        std::cout << '\n';
      }
      std::cout << " - actions & gotoes:\n";
      int state = items->Number();
      for(auto unit : mp.Unitset()) {
        int lo = mp.Loc(unit.Tag());
        if(actions[state][lo] != "ERROR")
          std::cout << " - " << mp[unit.Tag()] << ' '
            << actions[state][lo] << '\n';
      }
      std::cout << '\n';
    }
    std::cout << " ============= ACTIONS =============\n";
  }

} // namespace message

#endif
