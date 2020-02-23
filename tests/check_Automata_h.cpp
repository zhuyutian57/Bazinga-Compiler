/*-----------------------------------------------
*	Filename: check_Automata_h.cpp
*	Author: zhuyutian
*	Date: 2020.02.17
-----------------------------------------------*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define mpii(a, b) make_pair(a, b)
const int maxn = 2333;
const int INF = 1 << 30;
const double eps = 1e-6;
const int mod = 1000000007;

#include <unordered_map>
#include "../lexer/Automata.h"

int id = 0;


int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
  lexer::Automata *t = new lexer::Automata();
  t->Build("./regular_defination/regular_defination.rd");
  cout << "State size : "<< t->State_size() << endl;
	cout << "DFA begin : " << t->Begin() << endl;
  cout << "Alphabet :";
  for(auto x : *t->Alphabet())
    cout << ' ' << x;
  cout << endl;
  for(int i = 0; i < t->State_size(); i++) {
    cout << "State - " << i << " ------------\n";
    cout << "Positions :";
    for(auto x : *(t->Pos_sets(i)))
      cout << ' ' << x;
    cout << endl;
    cout << "Edges :\n";
    for(auto ch : *t->Alphabet()) {
      if(t->Goto(i, ch) == -1)
        continue;
      cout << ' ' << ch << " - "
        << t->Goto(i, ch) << '\n';
    }
    cout << '\n';
  }
  return 0;
}
