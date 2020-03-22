/*-----------------------------------------------
*	Filename: test.cpp
*	Author: zhuyutian
*	Date: 2020.02.13
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

#include "../lexer/Lexer.h"

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	lexer::Lexer* t = new lexer::Lexer();
  const char *rdp = "../regular_definations/regular_defination.rd";
  const char *scp = "../source_codes/1.bzg";
  cout << t->Build(rdp) << '\n';
  cout << t->Analyze(scp) << '\n';
  return 0;
}
