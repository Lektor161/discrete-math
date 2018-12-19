#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

ifstream fin("part2num.in");
ofstream fout("part2num.out");

int main() {
	string a;
	fin >> a;
	int cur = 0, n = 0, m = 0;
	ll answ = 0;
	vector<int> all;

	for (int i = 0; i < a.length(); i++) {
		if (isdigit(a[i])) {
			cur *= 10;
			cur += (a[i] - '0');
		} else {
			all.push_back(cur);
			n += cur;
			cur = 0;
		}
	}
	if (cur) {
		all.push_back(cur);
		n += cur;
	}
	m = all.size();

	vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				dp[i][j] = 1;
			} else {
				for (int d = j; d <= i; d++) {
					dp[i][j] += dp[i - j][d];
				}
			}
		}
	}

	int sl = 1;
	for (int i = 0; i < m; i++) {
		for (; sl < all[i]; sl++) {
			answ += dp[n][sl];
		}
		n -= sl;
	}

	fout << answ;

	fin.close();
	fout.close();
	return 0;
}
