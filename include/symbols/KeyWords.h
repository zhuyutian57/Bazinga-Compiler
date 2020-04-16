
#include "UnitSet.h"

#ifndef _KEYWORDS_H_
#define _KEYWORDS_H_

namespace symbols {

namespace KeyWords {

  static Unit* const End = new Unit(Tag::END);
  static Type* const Int = new Type("int", Tag::TYPE, 4);
  static Type* const Float = new Type("float", Tag::TYPE, 4);

} // namespace KeyWords

} // namespace symbols

#endif
