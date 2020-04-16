
#include "Type.h"

using namespace symbols;

Type::Type(const std::string& s, int tag, int w)
  : Terminal(s, tag), width(w) {}

const int& Type::Width() const { return width; }
