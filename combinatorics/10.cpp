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

int n;

vector<int> a;

ifstream fin("partition.in");
ofstream fout("partition.out");

void gen(int p, int sum) {
	if(sum == n) {
		for (int i = 0; i < p; i++) {
			fout << a[i];
			if (i < p - 1) fout << "+";
		}
		fout << endl;
	} else {
		int st = 1;
		if (p) st = a[p - 1];
		for (int i = st; i <= n - sum; i++) {
			a[p] = i;
			gen(p + 1, sum + i);
		}
	}
}

int main()
{
	fin >> n;
	a.resize(n);
	gen(0, 0);
	fout.close();
	fin.close();
}