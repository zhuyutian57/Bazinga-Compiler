
#include "Terminal.h"

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace symbols {

inline namespace terminals {

class Integer : public Terminal {

public:
  Integer(const std::string&);
  ~Integer() {}

  const int Val();

private:
  int val;

}; // class Integer

} // namespace terminals

} // namespace symbols

#endif
