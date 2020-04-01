
#include "Automata.h"

#include "../symbol/UnitSet.h"
#include "../symbol/KeyWords.h"
using namespace symbol;

#ifndef _LEXER_H_
#define _LEXER_H_

namespace lexer {

class Lexer {

public:
  Lexer() : cur(0) {/*{{{*/
    dfa = new Automata();
    
    Reserve(new Terminal(';')); Reserve(new Terminal('+'));
    Reserve(new Terminal('-')); Reserve(new Terminal('*'));
    Reserve(new Terminal('/')); Reserve(new Terminal('='));
    Reserve(new Terminal('(')); Reserve(new Terminal(')'));
    
    Reserve(KeyWords::Int);
    Reserve(KeyWords::Float);
  }
  ~Lexer() {
    for(auto p : words) {
      Unit* uptr = (Unit*)p.second;
      if(uptr->Tag() != Tag::TYPE)
        delete uptr;
    }
    delete dfa;
  }/*}}}*/

  bool Build(const char* regular_definations) {/*{{{*/
    dfa->Build(regular_definations);
    return true;
  }/*}}}*/

  bool Analyze(const char* source_codes) {/*{{{*/
    if(!AnalyzeSourceCode(source_codes)) {
      Error("Fail to build DFA!");
      return false;
    }
    InformationsOfTokens();
    tokens.push_back(KeyWords::End);
    return true;
  }/*}}}*/

  // Return a terminal everytime
  Terminal* Next_terminal() {/*{{{*/
    return (Terminal*)tokens[cur++];
  }/*}}}*/

private:
  Automata *dfa;
  std::vector<void*> tokens;
  std::unordered_map<std::string, void*> words; 

  int cur;

  struct Buf {/*{{{*/
    int cur;
    std::vector<char> chv;
    Buf(const char* path) : cur(0) {
      std::fstream in(path, std::ios::in);
      while(in.peek() != EOF) chv.push_back(in.get());
    }
    bool eof() { return cur >= chv.size(); }
    char peek() { return chv[cur]; }
    char get() { cur++; return chv[cur - 1]; }
    void ignore(int i) { while(i--) cur++; } 
    int tellg() { return cur; }
    void seekg(int i) { cur = i; }
    
    std::string get(int beg, int count) {
      std::string s = "";
      while(count--) s += chv[beg++];
      return s;
    }
  }; // struct Buf}}}


private:
  inline void Reserve(const Terminal* w) {/*{{{*/
    words[w->Lexeme()] = (void*)w;
  }/*}}}*/

  void AddNewWord(const std::string& word) {/*{{{*/
    if(word[0] >= '0' && word[0] <= '9') {
      if(word.find('.') != std::string::npos) {
        Reserve(new Real(word));
      } else {
        Reserve(new Integer(word));
      }
    } else {
      Reserve(new Terminal(word, Tag::ID));
    }
  }/*}}}*/

  void Recognize(const std::string& word) {/*{{{*/
    if(words.find(word) == words.end())
      AddNewWord(word);
    tokens.push_back(words[word]);
  }/*}}}*/

  bool AnalyzeSourceCode(const char* source_code) {/*{{{*/
    Buf buf(source_code);
    // Read a word every circulation
    while(!buf.eof()) {
      dfa->Reset();
      while(buf.peek() == ' ' || buf.peek() == '\n')
        buf.ignore(1);
      if(buf.eof()) break;
      int beg = buf.tellg();
      int end = beg - 1;
      while(!buf.eof() && dfa->Goto(buf.peek()) != -1) {
        if(dfa->Accepted()) end = buf.tellg();
        buf.ignore(1);
      }
      if(beg > end) return false;
      Recognize(buf.get(beg, end - beg + 1));
      buf.seekg(end + 1);
    }
    return true;
  }/*}}}*/

  void InformationsOfTokens() {/*{{{*/
    std::cout << " Token stream : \n";
    std::string sym = ";+-*/=()";
    for(auto addr : tokens) {
      Unit *t = (Unit*)addr;
      Terminal *p = (Terminal*)addr;
      std::cout << '<' << p->Tag() << ',';
      std::cout << '\t' << p->Lexeme() << ',';
      std::cout << '\t' << words[p->Lexeme()] << ">\n";
    }
  }/*}}}*/


}; // class Lexer

} // namespace lexer

#endif
