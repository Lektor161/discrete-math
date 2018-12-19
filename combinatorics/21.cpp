//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

ll n, k;
vector<int> a;
vector<vector<ll>> dp;

ifstream fin("num2part.in");
ofstream fout("num2part.out");

void gen(int p, int sum) {
	if (p == sum) {
		a.push_back(p);
		return;
	}
	
	if (k <= dp[sum][p]) {
		a.push_back(p);
		gen(p, sum - p);
	}
	else {
		k -= dp[sum][p];
		gen(p + 1, sum);
	}
}

int main() {
	fin >> n >> k;
	k++;
	dp.resize(n + 1, vector<ll>(n + 1, 0));
	// stupid dp with sum and first num
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) dp[i][j] = 1;
			else {
				for (int d = j; d <= i; d++) {
					dp[i][j] += dp[i - j][d];
				}
			}
		}
	}

	gen(0, n);
	
	for (int i = 0; i < a.size(); i++) {
		fout << a[i];
		if (i < a.size() - 1) fout << "+";
	}

	fin.close();
	fout.close();
	return 0;
}
