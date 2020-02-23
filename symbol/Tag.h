
#ifndef _TAG_H_
#define _TAG_H_

namespace symbol {

class Tag {

/* Encode the unite of token's sorts
 * */

public:
  
  // Types
  // int, float
  const static int BASIC = 300;

  // Variables
  const static int ID = 301;

  // Data types
  const static int INTEGER = 302, FLOAT = 303;

}; // class Tag

} // namespace symbol

#endif
