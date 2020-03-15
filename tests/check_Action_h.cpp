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

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	const char *g_path = "../parser/grammars/test.cfg";
  parser::Action *ac_table = new parser::Action();
  cout << ac_table->Build(g_path) << endl;
  
	return 0;
}
/*
P -> S
S -> L = R
S -> R
L -> * R
L -> ID
R -> L
 * */
