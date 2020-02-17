
#include <set>

namespace lexer {

class Info {

public:
  Info() {
    firstpos = new std::set<int>;
    lastpos = new std::set<int>;
  }

  bool Nullable() { return nullable; }
  std::set<int>* Firstpos() { return firstpos; }
  std::set<int>* Lastpos() { return lastpos; }

  void Set_nullable(bool t) {
    nullable = t;
  }
  void Set_firstpos(std::set<int>* t) {
    firstpos = t;
  }

private:
  bool nullable;
  std::set<int> *firstpos, *lastpos;

}; // Info

} // lexer

