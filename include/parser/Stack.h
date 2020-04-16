
#include "Stl.h"

#ifndef _STACK_H_
#define _STACK_H_

namespace parser {

template<typename ValType>
class Stack {

public:
  Stack();
  ~Stack() {}
  
  ValType operator[](const int&) const;
  bool Empty() const;
  void Push(const ValType&); 
  void Pop();
  std::size_t Size() const;
  ValType& Top();

private:
  std::vector<ValType> v;

}; // class Stack

}// namespace parser

#endif
