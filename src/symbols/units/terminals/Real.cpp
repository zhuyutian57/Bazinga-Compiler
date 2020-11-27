
#include "Real.h"

using namespace symbols;

Real::Real(const std::string& s)
  : Word(s, Tag::REAL), val(std::stof(s)) {} 

const int Real::Val() { return val; }
