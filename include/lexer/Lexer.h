
#include "Automata.h"
#include "UnitSet.h"
#include "KeyWords.h"

using namespace symbols;

#ifndef _LEXER_H_
#define _LEXER_H_

namespace lexer {

class Lexer {

public:
  Lexer();
  ~Lexer();

  bool Build(const char*);
  bool Analyze(const char*);
  Terminal* NextTerminal();

private:
  int current_state;
  Automata *dfa;
  std::vector<void*> tokens;
  std::unordered_map<std::string, void*> words; 

  struct Buf {
    int cur;
    std::vector<char> chv;
    Buf(const char* path) : cur(0) {
      std::fstream in(path, std::ios::in);
      while(in.peek() != EOF) chv.push_back(in.get());
    }
    bool eof() { return cur >= chv.size(); }
    char peek() { return chv[cur]; }
    char get() { return chv[cur++]; }
    void ignore(int i) { while(i--) cur++; } 
    int tellg() { return cur; }
    void seekg(int i) { cur = i; }
    
    std::string get(int beg, int count) {
      std::string s = "";
      while(count--) s += chv[beg++];
      return s;
    }
  }; // struct Buf


private:
  void Reserve(const Terminal*);
  void AddNewWord(const std::string&);
  void Recognize(const std::string&);
  bool AnalyzeSourceCode(const char*);
  void InformationsOfTokens();

}; // class Lexer

} // namespace lexer

#endif
