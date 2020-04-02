
#include <vector>

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

namespace parser {

class Product {

public:
  Product() {}
  ~Product() {}

  int Number() { return number; }
  int Head() { return head; }
  const int Body(const int i) {
    if(i >= bodies.size())
      return -1;
    return bodies[i];
  }
  const int BodySize() { return bodies.size(); }

  void SetNumber(const int num) { number = num; }
  void SetHead(const int h) { head = h; }
  void AddBody(const int b) { bodies.push_back(b); }

private:
  int               number;
  int               head;
  std::vector<int>  bodies;

}; // class Product

} // namespace parser

#endif

