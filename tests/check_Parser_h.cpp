/*-----------------------------------------------
*	Filename: check_parser_h.cpp
*	Author: zhuyutian
*	Date: 2020.03.28
-----------------------------------------------*/
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define mkp(a, b) make_pair(a, b)
const int maxn = 100005;
const int INF = 1 << 30;
const ll LINF = 1ll << 60;
const double eps = 1e-6;
const int mod = 1000000007;

#include "../parser/Parser.h"

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
  const char *rdp =
    "../config/regular_defination.rd";
  const char *gp =
    "../config/grammars.cfg";
  const char *scp =
    "../config/1.bzg";
  parser::Parser *lrp = new parser::Parser();
  lrp->Build(rdp, gp);
  if(!lrp->Analyze(scp)) {
    cout << "fuckfuckfuck" << endl;
  }
	return 0;
}
