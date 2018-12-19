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

int n, k;
vector<bool> was;
vector<int> a;
ifstream fin("choose.in");
ofstream fout("choose.out");

void gen(int p) {
	if(p == k) {
		for (int i = 0; i < k; i++) fout << a[i]+1 << " ";
		fout << endl;
	} else {
		int start = 0, to = n-(k-p-1);
		if (p) start = a[p - 1] + 1;
		for (int i = start; i < to; i++) {
			if (!was[i]) {
				was[i] = true;
				a[p] = i;
				gen(p + 1);
				was[i] = false;
			}
		}
	}
}

int main()
{
	fin >> n >> k;
	a.resize(k);
	was.resize(n, false);
	gen(0);
	fout.close();
	fin.close();
}