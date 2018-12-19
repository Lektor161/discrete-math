//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

int main() {
	ifstream fin("num2brackets2.in");
	ofstream fout("num2brackets2.out");
	
	ll n, k;
	fin >> n >> k;
	k++;
	string ans = "", last_no_friend = "";

	vector<vector<ll>> dp(2 * n + 1, vector<ll>(n + 1, 0));

	// stupid dp with len and d
	dp[0][0] = 1;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j < n) dp[i + 1][j + 1] += dp[i][j];
			if (j) dp[i + 1][j - 1] += dp[i][j];
		}
	}
	
	ll d = 0, cur;

	for (int i = 2*n - 1; i >= 0; i--) {
		if (d < n) cur = dp[i][d + 1] << (i - d - 1) / 2;
		else cur = 0;

		if (cur >= k) {
			ans.push_back('(');
			last_no_friend.push_back('(');
			d++;
			continue;
		}
		k -= cur;

		if (last_no_friend.length() && d && last_no_friend.back() == '(') cur = dp[i][d - 1] << (i - d + 1) / 2;
		else cur = 0;
		
		if (cur >= k) {
			ans.push_back(')');
			last_no_friend.erase(--last_no_friend.end());
			d--;
			continue;
		}
		k -= cur;


		if (d < n) cur = dp[i][d + 1] << (i - d - 1) / 2;
		else cur = 0;

		if (cur >= k) {
			ans.push_back('[');
			last_no_friend.push_back('[');
			d++;
			continue;
		}
		k -= cur;
		ans.push_back(']');
		last_no_friend.erase(--last_no_friend.end());
		d--;
	}

	fout << ans;
	fin.close();
	fout.close();
	return 0;
}