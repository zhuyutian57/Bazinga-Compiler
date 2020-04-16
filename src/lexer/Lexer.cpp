
#include "Lexer.h"

using namespace bin;
using namespace lexer;

Lexer::Lexer() : current_state(0) {
  dfa = new Automata();
  
  Reserve(new Terminal(';')); Reserve(new Terminal('+'));
  Reserve(new Terminal('-')); Reserve(new Terminal('*'));
  Reserve(new Terminal('/')); Reserve(new Terminal('='));
  Reserve(new Terminal('(')); Reserve(new Terminal(')'));
  
  Reserve(KeyWords::Int);
  Reserve(KeyWords::Float);
}
Lexer::~Lexer() {
  for(auto p : words) {
    Unit* uptr = (Unit*)p.second;
    if(uptr->Tag() != Tag::TYPE)
      delete uptr;
  }
  delete dfa;
}

bool Lexer::Build(const char* regular_definations) {
  dfa->Build(regular_definations);
  Print("Lexer is ok!");
  return true;
}

bool Lexer::Analyze(const char* source_codes) {
  if(!AnalyzeSourceCode(source_codes)) {
    Error("Fail to build DFA!");
    return false;
  }
  InformationsOfTokens();
  tokens.push_back(KeyWords::End);
  return true;
}

// Return a terminal everytime
Terminal* Lexer::NextTerminal() {
  return (Terminal*)tokens[current_state++];
}

void Lexer::Reserve(const Terminal* w) {
  words[w->Lexeme()] = (void*)w;
}

void Lexer::AddNewWord(const std::string& word) {
  if(word[0] >= '0' && word[0] <= '9') {
    if(word.find('.') != std::string::npos) {
      Reserve(new Real(word));
    } else {
      Reserve(new Integer(word));
    }
  } else {
    Reserve(new Terminal(word, Tag::ID));
  }
}

void Lexer::Recognize(const std::string& word) {
  if(words.find(word) == words.end())
    AddNewWord(word);
  tokens.push_back(words[word]);
}

bool Lexer::AnalyzeSourceCode(const char* source_code) {
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
}

void Lexer::InformationsOfTokens() {
  std::cout << " Token stream : \n";
  std::string sym = ";+-*/=()";
  for(auto addr : tokens) {
    Unit *t = (Unit*)addr;
    Terminal *p = (Terminal*)addr;
    std::cout << '<' << p->Tag() << ',';
    std::cout << '\t' << p->Lexeme() << ',';
    std::cout << '\t' << words[p->Lexeme()] << ">\n";
  }
}
