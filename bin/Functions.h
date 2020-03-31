
#include <iostream>
#include <set>
#include <string>

#ifndef _FUNTIONS_H_
#define _FUNTIONS_H_

namespace bin {
 
template<typename T>  
void MoveSetToSet(const std::set<T>* out, std::set<T>* in) {
  for(auto e : (*out)) in->insert(e);
}

} // namespace bin

#endif
