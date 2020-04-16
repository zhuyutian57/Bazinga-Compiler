
#include "Parser.h"
using namespace parser;

Parser::Parser() : lok(NULL), entry_Size(0) {
  env = new Env();
  lex = new Lexer();
  action_table = new Action();
  reduce_funcs.push_back(NULL); // Accepted
  reduce_funcs.push_back(std::bind(&Reduce_01, this));
  reduce_funcs.push_back(std::bind(&Reduce_02, this));
  reduce_funcs.push_back(std::bind(&Reduce_03, this));
  reduce_funcs.push_back(std::bind(&Reduce_04, this));
  reduce_funcs.push_back(std::bind(&Reduce_05, this));
  reduce_funcs.push_back(std::bind(&Reduce_06, this));
  reduce_funcs.push_back(std::bind(&Reduce_07, this));
  reduce_funcs.push_back(std::bind(&Reduce_08, this));
  reduce_funcs.push_back(std::bind(&Reduce_09, this));
  reduce_funcs.push_back(std::bind(&Reduce_10, this));
  reduce_funcs.push_back(std::bind(&Reduce_11, this));
  reduce_funcs.push_back(std::bind(&Reduce_12, this));
  reduce_funcs.push_back(std::bind(&Reduce_13, this));
  reduce_funcs.push_back(std::bind(&Reduce_14, this));
  reduce_funcs.push_back(std::bind(&Reduce_15, this));
  reduce_funcs.push_back(std::bind(&Reduce_16, this));
  reduce_funcs.push_back(std::bind(&Reduce_17, this));
}
Parser::~Parser() {
  delete env;
  delete lex;
  delete action_table;
}

bool Parser::Build(const char* regular_definations, 
    const char* grammars) {
  if(!lex->Build(regular_definations)) return false;
  if(!action_table->Build(grammars)) return false;
  Print("Parser is ok!");
  return true;
}

bool Parser::Analyze(const char* source_code) {
  if(!lex->Analyze(source_code)) return false; 
  e_stack.Push(new State(0, KeyWords::End));
  lok = lex->NextTerminal();
  while(true) {
    const ACTION_STATE& s = e_stack.Top()->StateNumber();
    const int& t = lok->Tag();
    const std::string& action = action_table->ACTION(s, t);
    CurrentState(action);
    if(action[0] == 'S') {
      const int n_state =
        std::stoi(action.substr(1, action.size()));
      e_stack.Push(new State(n_state, lok));
      lok = lex->NextTerminal();
    } else if(action[0] == 'R') {
      const int product_index =
        std::stoi(action.substr(1, action.size())); 
      if(!Reduce(product_index)) {
        Error("fuck"); return false;
      }
    } else if(action == ACCEPTED) {
      Print("ACCEPTED! NO ERROE! CONGRATULATIONS!"); 
      break;
    } else {
      Error("what's this?");
      return false;
    }
  }
  return true;
}

void Parser::CurrentState(const std::string& ac) {
  int left = 48;
  for(int i = e_stack.Size(); i; i--) {
    int s = e_stack[-i]->StateNumber();
    std::cout << s << ' ';
    left -= 1 + std::to_string(s).size();
  }
  for(int i = 0; i < left; i++) std::cout << ' ';
  left = 72;
  std::cout << action_table->Units()[((Unit*)lok)->Tag()] << '\t';
  left -= 1 + action_table->Units()[((Unit*)lok)->Tag()].size();
  for(int i = 1; i <= e_stack.Size(); i++) {
    Unit *uptr = (Unit*)GetGrammarSymbol(-i);
    left -= action_table->Units()[uptr->Tag()].size() + 1;
    std::cout << action_table->Units()[uptr->Tag()] << ' ';
  }
  for(int i = 0; i < left; i++) std::cout << ' ';
  std::cout << ac << '\n';
}

void Parser::Shift(
    const ACTION_STATE& state, void* input_ptr) {
  e_stack.Push(new State(state, input_ptr));
}

int Parser::Goto(const ACTION_STATE& s, Unit* unit) {
  const std::string& ac = action_table->ACTION(s, unit->Tag());
  if(ac == ACTION_ERROR) return -1;
  return std::stoi(ac);
}

void* Parser::GetGrammarSymbol(const int index) {
  return e_stack[index]->GrammarSymbol();
}

ENTRY Parser::NewEntry() {
  return std::string("t")
    + std::to_string(++entry_Size);
}

void Parser::GenerateIntermediateCode(const std::string& inter_code) {
  Print(inter_code);
}

ENTRY Parser::TypeTransform(
    const ENTRY& entry, const Type *type_1, const Type *type_2) {
  ENTRY n_entry = NewEntry();
  GenerateIntermediateCode(n_entry + " = " + type_1->Lexeme()
      + "to" + type_2->Lexeme() + " " + entry);
  return entry;
}

Type* Parser::MaxType(Type* type_1,Type* type_2) {
  if(type_1->Tag() > type_2->Tag())
    return type_1;
  return type_2;
}
Type* Parser::min_type(Type* type_1,Type* type_2) {
  if(type_1->Tag() < type_2->Tag())
    return type_1;
  return type_2;
}

bool Parser::CheckProduct(const int& product_index) {
  Product* const product = action_table->GetProduct(product_index);
  if(product->Body(0) == Tag::EPSILON) return true;
  const int n = product->BodySize();
  for(int i = 0; i < n; i++) {
    const TAG b = product->Body(i);
    const TAG t = ((Unit*)GetGrammarSymbol(i - n))->Tag();
    if(b != t) return false;
  }
  return true;
}
