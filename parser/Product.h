
#include <vector>

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

namespace parser {

class Product {

public:
  Product(){}
  ~Product(){}

  int Number() { return number; }
  int Head() { return head; }
  const int Next_body(const int i) {
    if(i >= bodies.size())
      return -1;
    return bodies[i];
  }

  void Set_number(const int num) {
    number = num;
  }
  void Set_head(const int h) { head = h; }
  void Add_body(const int b) {
    bodies.push_back(b);
  }

private:
  int number;
  int head;
  std::vector<int> bodies;

}; // class Product

} // namespace parser

#endif

