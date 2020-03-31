
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Automata.h"
#include "Float.h"
#include "Integer.h"
#include "Type.h"

#ifndef _LEXER_H_
#define _LEXER_H_

namespace lexer {

class Lexer {

private:
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

public:
  Lexer() : cur(0) {/*{{{*/
    dfa = new Automata();
    words = new std::unordered_map<std::string, void*>;
    tokens = new std::vector<void*>;
   
    reserve(new Terminal(';')); reserve(new Terminal('+'));
    reserve(new Terminal('-')); reserve(new Terminal('*'));
    reserve(new Terminal('/')); reserve(new Terminal('='));
    reserve(new Terminal('(')); reserve(new Terminal(')'));
    reserve(new Type("int", Tag::TYPE, 4));
    reserve(new Type("float", Tag::TYPE, 8));
  }
  ~Lexer() {
    for(auto p : (*words)) {
      Unit* ptr = (Unit*)p.second;
      if(ptr->Tag() != Tag::TYPE)
        delete ptr;
    }
    delete dfa, words, tokens;
  }/*}}}*/

  bool Build(const char* regular_definations) {/*{{{*/
    dfa->Build(regular_definations);
    return true;
  }/*}}}*/

  bool Analyze(const char* source_codes) {/*{{{*/
    if(!analyze(source_codes)) {
      Error("Fail to build DFA!");
      return false;
    }
    bin::InfoLexer(words, tokens);
    tokens->push_back(new Terminal(Tag::END));
    return true;
  }/*}}}*/

  // Return a terminal everytime
  Terminal* Next_terminal() {/*{{{*/
    return (Terminal*)(*tokens)[cur++];
  }/*}}}*/

private:
  Automata *dfa;
  std::unordered_map<std::string, void*>* words; 
  std::vector<void*>* tokens;

  int cur;

private:
  inline void reserve(const Terminal* w) {/*{{{*/
    (*words)[w->Lexeme()] = (void*)w;
  }/*}}}*/

  void add_new_word(const std::string& word) {/*{{{*/
    if(word[0] >= '0' && word[0] <= '9') {
      if(word.find('.') != std::string::npos) {
        reserve(new Float(word));
      } else {
        reserve(new Integer(word));
      }
    } else {
      reserve(new Terminal(word, symbol::Tag::ID));
    }
  }/*}}}*/

  void recognize(const std::string& word) {/*{{{*/
    if(words->find(word) == words->end())
      add_new_word(word);
    tokens->push_back((*words)[word]);
  }/*}}}*/

  bool analyze(const char* source_code) {/*{{{*/
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
        if(dfa->Accepted())
          end = buf.tellg();
        buf.ignore(1);
      }
      if(beg > end) return false;
      recognize(buf.get(beg, end - beg + 1));
      buf.seekg(end + 1);
    }
    return true;
  }/*}}}*/

}; // class Lexer

} // namespace lexer

#endif
