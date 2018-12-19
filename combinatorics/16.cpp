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

ifstream fin("choose2num.in");
ofstream fout("choose2num.out");

int main()
{
	int n, k;
	fin >> n >> k;
	ll ans = 0;
	vector<vector<ll>> c(n+1);
	vector<int> a(k+1, 0);

	for (int i = 0; i <= n; i++) {
		c[i].resize(i + 1, 1);
		for (int j = 1; j < i; j++) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]);
		}
	}

	for (int i = 1; i <= k; i++) fin >> a[i];

	for (int i = 1; i <= k; i++) {
		for (int j = a[i - 1] + 1; j <= a[i] - 1; j++) ans += c[n - j][k - i];
	}
	fout << ans;
	fout.close();
	fin.close();
}