//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

int main() {
	ifstream fin("brackets2num.in");
	ofstream fout("brackets2num.out");
	string s;
	fin >> s;
	int n = s.length();
	vector<vector<ll>> dp(2 * n + 1, vector<ll>(n+1, 0));

	// stupid dp with len and balance
	dp[0][0] = 1;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j < n) dp[i + 1][j + 1] += dp[i][j];
			if (j) dp[i + 1][j - 1] += dp[i][j];
		}
	}

	ll ans = 0;
	int d = 0;

	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			d++;
		}
		else {
			ans += dp[n - i - 1][d + 1];
			d--;
		}
	}
	fout << ans;
	fin.close();
	fout.close();
	return 0;
}
