
#include <string>

#include "Tag.h"
#include "Word.h"

namespace symbol {

class Float : public Word {

public:
  Integer(const std::string& s)
    : Word(s, Tag::FLOAT), val(std::stof(s)) {} 

private:
  float val;

}; // Float

} // symbol

