
#include "Id.h"

using namespace symbols;

Id::Id(const std::string& s, terminals::Type *t)
  : name(s), type(t) {}
Id::~Id() { delete type; }

const std::string& Id::Name() { return name; }

terminals::Type* Id::Type() { return type; }
