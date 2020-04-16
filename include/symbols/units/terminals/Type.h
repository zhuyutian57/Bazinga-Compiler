
#include "Terminal.h"

#ifndef _TYPE_H_
#define _TYPE_H_

namespace symbols {

inline namespace terminals {

class Type : public Terminal {

public:
  Type(const std::string&, int, int);
  ~Type() {}

  const int& Width() const;

private:
  int width;

}; // class Type

} // namespace terminals

} // namespace symbols

#endif
