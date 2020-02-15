/*-----------------------------------------------
*	Filename: check_Ast_h.cpp
*	Author: zhuyutian
*	Date: 2020.02.14
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

#include "../lexer/Ast.h"

void dfs(lexer::Node* p) {
	if(p == NULL) return;
	if(p->Nt() == lexer::LEAF) cout << p->Ch();
	if(p->Nt() == lexer::OR) {
		//cout << '(';
		dfs(p->Ls());
		cout << '|';
		dfs(p->Rs());
		//cout << ')';
	}
	if(p->Nt() == lexer::CAT) {
		dfs(p->Ls());
		//cout << ' ';
		dfs(p->Rs());
	}
	if(p->Nt() == lexer::STAR) {
		cout << '(';
		dfs(p->Ls());
		cout << ")*";
	}
	if(p->Nt() == lexer::PLUS) {
		cout << '(';
		dfs(p->Ls());
		cout << ")+";
	}
}

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	lexer::Ast *t = new lexer::Ast();
	//dfs(t->Tree("digits"));
	//cout << '\n';
	//dfs(t->Tree("letters"));
	//cout << '\n';
	t->Regonize("../lexer/regular_defination.rd");
	cout << "ok" << endl;
	dfs(t->Tree("Lexeme"));
	cout << endl;
	return 0;
}
