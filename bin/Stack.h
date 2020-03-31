
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
  T operator[](const int& index) const {
    return v[v.size() + index];
  }

  bool Empty() const { return v.empty(); }
  
  void Push(const T& e) { v.push_back(e); }
  
  void Pop() { v.pop_back(); }

  std::size_t Size() const { return v.size(); }

  T& Top() { return v.back(); }

private:
  std::vector<T> v;

}; // class Stack

}// namespace bin

#endif
