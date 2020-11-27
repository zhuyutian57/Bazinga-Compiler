
#include "Integer.h"

using namespace symbols;

Integer::Integer(const std::string& s)
  : Word(s, Tag::INTEGER), val(std::stoi(s)) {} 

const int Integer::Val() { return val; }
