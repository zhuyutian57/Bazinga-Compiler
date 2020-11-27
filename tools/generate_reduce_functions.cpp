
#include <iostream>
#include <string>
using namespace std;

int main() {
  freopen("./config/grammars.cfg", "r", stdin);
  string product, num;
  for(int i = 0; getline(cin, product); i++) {
    if(i == 0) continue;
    cout << "  // " + product << '\n';
    num = to_string(i);
    if(i < 10) num = "0" + num;
    cout << "  void* Reduce_" + num + "();"<< '\n';
  }
  return 0;
}
