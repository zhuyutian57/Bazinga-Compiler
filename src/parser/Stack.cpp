
#include "Stack.h"
#include "State.h"

using namespace parser;

template<typename ValType>
Stack<ValType>::Stack() { v.clear(); }

//TODO add exception
template<typename ValType>
ValType Stack<ValType>::operator[](const int& index) const {
  return v[v.size() + index];
}

template<typename ValType>
bool Stack<ValType>::Empty() const { return v.empty(); }

template<typename ValType>
void Stack<ValType>::Push(const ValType& e) { v.push_back(e); }

template<typename ValType>
void Stack<ValType>::Pop() { v.pop_back(); }

template<typename ValType>
std::size_t Stack<ValType>::Size() const { return v.size(); }

template<typename ValType>
ValType& Stack<ValType>::Top() { return v.back(); }

template class Stack<State*>;
