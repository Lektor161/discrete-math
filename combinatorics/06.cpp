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

int n, ans = 0;

vector<int> a;

ifstream fin("vectors.in");
ofstream fout("vectors.out");

void maddde(int p, int c = 0) {
	if (p == n) {
		bool check = true;
		for (int i = 0; i < n - 1; i++) {
			if (a[i] == 1 && a[i + 1] == 1) check = false;
		}
		if (check && c) {
			for (int i = 0; i < n; i++) fout << a[i];
			fout << endl;
		}
		if (check) ans++;
	}
	else {
		a[p] = 0;
		maddde(p + 1, c);
		a[p] = 1;
		maddde(p + 1, c);
	}
}

int main()
{
	fin >> n;
	a.resize(n);
	maddde(0);
	fout << ans << endl;
	maddde(0, 1);
	fout.close();
	fin.close();
}