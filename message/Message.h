
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lexer/Word.h"

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace message {

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
      lexer::Token *t = (lexer::Token*)addr;
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

} // namespace message

#endif
