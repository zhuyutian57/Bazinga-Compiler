
#include <set>

#ifndef _FUNTIONS_H_
#define _FUNTIONS_H_

namespace bin {
 
template<typename T>  
void move_set2set(std::set<T>* in, 
    const std::set<T>* out) {
  for(auto e : (*out)) in->insert(e);
}

} // namespace bin

#endif
