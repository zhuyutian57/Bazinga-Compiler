
#include "Product.h"
using namespace parser;

int Product::Number() { return number; }
int Product::Head() { return head; }
const int Product::Body(const int i) {
  if(i >= bodies.size())
    return -1;
  return bodies[i];
}
const int Product::BodySize() { return bodies.size(); }

void Product::SetNumber(const int num) { number = num; }
void Product::SetHead(const int h) { head = h; }
void Product::AddBody(const int b) { bodies.push_back(b); }
