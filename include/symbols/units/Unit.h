
#include "Bin.h"
#include "Tag.h"

#ifndef _UNIT_H_
#define _UNIT_H_

namespace symbols {

#define TAG int
#define NONTERMINAL_BEGIN 400

class Unit {

public:
  Unit(const int);
  virtual ~Unit() {}

  bool operator==(const Unit&) const;
  bool operator<(const Unit&) const;

  const TAG& Tag() const;

protected:
  int tag;

}; // class Unit 

} // namespace symbols

#endif

