#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

int main() {
	ifstream fin("brackets2num2.in");
	ofstream fout("brackets2num2.out");
	string s;
	fin >> s;
	int n = s.length()/2, d = 0, t, suflen;
	ll ans = 0;
	vector<vector<ll>> dp(2 * n + 1, vector<ll>(n + 1, 0));

	dp[0][0] = 1;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j < n) dp[i + 1][j + 1] += dp[i][j];
			if (j) dp[i + 1][j - 1] += dp[i][j];
		}
	}
	

	string last_not_friend = "";

	for (int i = 0; i < s.length(); i++) {
		suflen = 2 * n - i - 1;

		if (s[i] == '(') {
			last_not_friend.push_back('(');
			d++;
			continue;
		}

		if (d < n) {
			t = d + 1;
			ans += dp[suflen][t] << ((suflen - t) / 2);
		}

		if (s[i] == ')') {
			last_not_friend.erase(--last_not_friend.end());
			d--;
			continue;
		}

		if (last_not_friend.length() && last_not_friend.back() == '(' && d) {
			t = d - 1;
			ans += dp[suflen][t] << ((suflen - t) / 2);
		}

		if (s[i] == '[') {
			last_not_friend.push_back('[');
			d++;
			continue;
		}

		if (d < n) {
			ans += dp[suflen][t] << ((suflen - t) / 2);
		}

		if (s[i] == ']') {
			last_not_friend.erase(--last_not_friend.end());
			d--;
		}
	}

	fout << ans;
	fin.close();
	fout.close();
	return 0;
}