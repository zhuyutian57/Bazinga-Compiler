
#include <vector>

#ifndef _STACK_H_
#define _STACK_H_

namespace bin {

template<typename T>
class Stack {

public:
  Stack() { v.clear(); }
  ~Stack() {}
  //TODO add exception
  T& operator[](const int& index) const {
    return v[v.size() + index];
  }

  bool empty() const { return v.empty(); }
  
  void push(const T& e) { v.push_back(e); }
  
  void pop() { v.pop_back(); }

  std::size_t size() const { return v.size(); }

  T& top() { return v.back(); }

private:
  std::vector<T> v;

}; // class Stack

}// namespace bin

#endif
