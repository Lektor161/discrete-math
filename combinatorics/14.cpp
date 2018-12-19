//#include "stdafx.h"
//#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;
typedef long long int ll;
typedef long double ld;

ifstream fin("perm2num.in");
ofstream fout("perm2num.out");

int main() {
	int n, k, q;
	ll res = 0, t;
	fin >> n;
	k = n;
	vector<int> col(n + 1, 0);
	vector<ll> fact(n + 1, 1);
	for (int i = 2; i <= n; i++) {
		col[i] = i - 1;
		fact[i] = fact[i - 1] * i;
	}
	for (int i = 1; i <= k; i++) {
		fin >> q;
		if (i == k) {
			res += col[q] + 1;
			fout << res-1;
			return 0;
		}
		t = fact[n - i] / fact[n - k];
		res += col[q] * t;
		//cout << col[q] << " " << t << endl;
		for (int j = q; j <= n; j++) col[j]--;
	}
	fin.close();
	fout.close();
}