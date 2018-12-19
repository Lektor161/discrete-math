//#include "stdafx.h"
//#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
typedef long long int ll;

int n,col=0,all=1;

vector<int> a;

ifstream fin("antigray.in");
ofstream fout("antigray.out");

void maddde(int p) {
	if (p == n) {
		col++;
		if (col > all) return;
		for (int i = 0; i < n; i++) fout << a[i];
		fout << endl;
		for (int i = 0; i < n; i++) fout << (a[i]+1)%3;
		fout << endl;
		for (int i = 0; i < n; i++) fout << (a[i]+2)%3;
		fout << endl;
	}
	else {
		a[p] = 0;
		maddde(p + 1);
		a[p] = 1;
		maddde(p + 1);
		a[p] = 2;
		maddde(p + 1);
	}
}

int main()
{
	fin >> n;
	for (int i = 0; i < n - 1; i++) all *= 3;
	a.resize(n);
	maddde(0);
	fout.close();
	fin.close();
}