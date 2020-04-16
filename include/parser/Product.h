
#include "Stl.h"

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

namespace parser {

class Product {

public:
  Product() {}
  ~Product() {}

  int Number();
  int Head();
  const int Body(const int);
  const int BodySize();
  void SetNumber(const int);
  void SetHead(const int);
  void AddBody(const int);

private:
  int               number;
  int               head;
  std::vector<int>  bodies;

}; // class Product

} // namespace parser

#endif

