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

#include "../lexer/Automata.h"

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
  lexer::Automata *t = new lexer::Automata();
  t->Build("../lexer/regular_defination.rd");
  cout << "ok" << endl;
  map<int, char>* mp = t->Posch();
  vector<set<int>* >& followpos = t->Followpos();
  cout << followpos.size() << endl;
  for(int i = 0; i < followpos.size(); i++) {
    cout << i << ' ' << (*mp)[i];
    for(auto x : (*followpos[i]))
      cout << ' ' << x;
    cout << endl;
  }
	return 0;
}
