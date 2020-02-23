
#include <string>

#include "Word.h"

#ifndef _TYPE_H_
#define _TYPE_H_

namespace symbol {

class Type : public Word {

public:
  Type(const std::string& s, int tag, int w)
    : Word(s, tag), width(w) {}

  const int& Width() const { return width; }

private:
  int width;

}; // class Type

} // namespace symbol

#endif
