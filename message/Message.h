
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../symbol/Word.h"

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
    for(auto addr : (*tokens)) {
      symbol::Word *p = (symbol::Word*)addr;
      std::cout << '<' << p->Tag() << ',';
      std::cout << p->Lexe() << ',';
      std::cout << (*words)[p->Lexe()] << ">\n";
    }
  }

} // namespace message

#endif
