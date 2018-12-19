//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

int main() {
	ifstream fin("num2brackets.in");
	ofstream fout("num2brackets.out");
	ll n, k;
	fin >> n >> k;
	k++;
	vector<vector<ll>> dp(2 * n + 1, vector<ll>(n+1, 0));

	// stupid dp with len and balance
	dp[0][0] = 1;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j < n) dp[i + 1][j + 1] += dp[i][j];
			if (j) dp[i + 1][j - 1] += dp[i][j];
		}
	}

	string ans = "";
	ll d = 0;

	for (ll i = 2 * n-1; i >= 0; i--) {
		if (d < n && dp[i][d + 1] >= k) {
			ans.push_back('(');
			d++;
		}
		else {
			ans.push_back(')');
			if (d < n) k -= dp[i][d+1];
			d--;
		}
	}
	fout << ans;
	fin.close();
	fout.close();
	return 0;
}
