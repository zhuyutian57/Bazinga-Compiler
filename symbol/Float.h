
#include <string>

#include "Word.h"

#ifndef _FLOAT_H_
#define _FLOAT_H_

namespace symbol {

class Float : public Word {

public:
  Float(const std::string& s)
    : Word(s, Tag::FLOAT), val(std::stof(s)) {} 

private:
  float val;

}; // class Float

} // namespace symbol

#endif
