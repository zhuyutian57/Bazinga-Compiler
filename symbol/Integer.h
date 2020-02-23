
#include <string>

#include "Word.h"

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace symbol {

class Integer : public Word {

public:
  Integer(const std::string& s)
    : Word(s, Tag::INTEGER), val(std::stoi(s)) {} 

private:
  int val;

}; // class Integer

} // namespace symbol

#endif
