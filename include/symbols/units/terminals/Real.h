
#include "Terminal.h"

#ifndef _REAL_H_
#define _REAL_H_

namespace symbols {

inline namespace terminals {

class Real : public Terminal {

public:
  Real(const std::string&);
  ~Real() {}

  const int Val();

private:
  float val;

}; // class Float

} // namespace terminals

} // namespace symbols

#endif
