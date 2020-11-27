
#include "Type.h"

#ifndef _KEYWORDS_H_
#define _KEYWORDS_H_

namespace symbols {

namespace Types {

  Type* const Int = new Type("int", Tag::TYPE, 4);
  Type* const Float = new Type("float", Tag::TYPE, 4);

} // namespace Types

} // namespace symbols

#endif
