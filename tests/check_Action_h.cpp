/*-----------------------------------------------
*	Filename: check_Action_h.cpp
*	Author: zhuyutian
*	Date: 2020.03.02
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

#include "../parser/Action.h"

#define FORMAT cout.width(8),cout.setf(ios::left)

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	const char *g_path = "../grammars/grammars.cfg";
  parser::Action *ac_table = new parser::Action();
  cout << ac_table->Build(g_path) << endl;
  parser::Units* uptr = ac_table->Units_ptr();
  vector<std::vector<std::string> >& acv = 
    ac_table->Actions();
  FORMAT;
  cout << "State";
  for(auto unit : uptr->Unitset()) {
    FORMAT;
    cout << (*uptr)[unit.Tag()];
  }
  cout << '\n';
  int number = 0;
  for(auto ac : acv) {
    FORMAT;
    cout << number++;
    for(auto s : ac) {
      FORMAT;
      if(s != "ERROR") cout << s;
      else cout << "-";
    }
    cout << '\n';
  } 
	return 0;
}
/*
0. P -> S
1. S -> L = R
2. S -> R
3. L -> * R
4. L -> ID
5. R -> L
 * */
