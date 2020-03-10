
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

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace bin {

  void error(const std::string& mes) {
    std:: cout << mes << '\n';
  }

  // Wrong regular defination
  void err_rd(
    const std::string& name,
    std::istringstream& ss) {
    std::cout<< name << " ->";
    std::string x;
    while(ss >> x) std::cout << " " + x;
    std::cout << " is not a regular defination\n";
  }
  
  void info_automata(
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
  }

  void info_lexer(
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
  }

  void info_action(
    const std::unordered_map<std::string, int>& unit_tags,
    const std::set<Unit>& units,
    const std::vector<parser::Product*>& products,
    const std::vector<parser::Items*>& items_set,
    const std::map<std::pair<int, int>, std::string>& actions,
    const std::map<std::pair<int, int>, int>& gotoes) {
    std::unordered_map<int, std::string> mp;
    for(auto p : unit_tags)
      mp[p.second] = p.first;
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
    for(auto items : items_set) {
      std::cout << " -Items " << items->Number();
      std::cout << " - " << items->Size() << " item-s\n";
      std::cout << " - kernel item:\n";
      for(auto item : items->Item_set()) {
        std::cout << " - "
          << item.Core().first << ' ' << item.Core().second << " ,";
        for(auto lok : item.Lookaheads())
          std::cout << ' ' << mp[lok];
      }
      std::cout << " - actions & gotoes:\n";
      for(auto unit : units) {
        std::pair<int, int> si
          = std::make_pair(items->Number(), unit.Tag());
        if(actions.find(si) != actions.end()) {
          std::cout << " - "<< mp[unit.Tag()]
            << "-" << actions.find(si)->second << '\n';
        }
        if(gotoes.find(si) != gotoes.end()) {
          std::cout << " - " << mp[unit.Tag()]
            << "-" << gotoes.find(si)->second << '\n';
        }
      }
      std::cout << '\n';
    }
    std::cout << " ============= ACTIONS =============\n";
  }

} // namespace message

#endif
