
#include <string>
#include <vector>

namespace lexer {

//TODO Discarded?
// Save characters for every terminal in regular definations
class Container {

public:
  Container(const std::string& s)
    : name(s) {}

  void insert(char c) { chv.push_back(c); }

private:
  std::string name;
  std::vector<char> chv;

}; // Container

} // lexer

