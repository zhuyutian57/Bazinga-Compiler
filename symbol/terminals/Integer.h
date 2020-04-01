
#include <string>

#include "Terminal.h"

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace symbol {

inline namespace terminals {

class Integer : public Terminal {

public:
  Integer(const std::string& s)
    : Terminal(s, Tag::INTEGER), val(std::stoi(s)) {} 

  const int& Val() { return val; }

private:
  int val;

}; // class Integer

} // namespace terminals

} // namespace symbol

#endif
