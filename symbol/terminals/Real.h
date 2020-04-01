
#include <string>

#include "Terminal.h"

#ifndef _REAL_H_
#define _REAL_H_

namespace symbol {

inline namespace terminals {

class Real : public Terminal {

public:
  Real(const std::string& s)
    : Terminal(s, Tag::REAL), val(std::stof(s)) {} 

private:
  float val;

}; // class Float

} // namespace terminals

} // namespace symbol

#endif
