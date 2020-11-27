
#include "Stl.h"

#ifndef _FUNTIONS_H_
#define _FUNTIONS_H_

namespace bin {

template<typename T> 
void MoveSetToSet(const std::set<T>* from, std::set<T>* to) {
  for(auto e : (*from)) to->insert(e);
}

template void MoveSetToSet(const std::set<int>*, std::set<int>*);
template void MoveSetToSet(const std::set<char>*, std::set<char>*);

} // namespace bin

#endif
