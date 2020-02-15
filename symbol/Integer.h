
#include <string>

#include "Tag.h"
#include "Word.h"

namespace symbol {

class Integer : public Word {

public:
  Integer(const std::string& s)
    : Word(s, Tag::INT), val(std::stoi(s)) {} 

private:
  int val;

}; // Integer

} // symbol

