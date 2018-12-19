#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int ll;

int main() {
	ifstream fin("nextpartition.in");
	ofstream fout("nextpartition.out");
	int cur = 0;
	string s;
	fin >> s;

	vector<int> all;

	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i])) {
			cur *= 10;
			cur += (s[i] - '0');
		} else {
			all.push_back(cur);
			cur = 0;
		}
	}

	if (cur) all.push_back(cur);
	int n = all[0];
	all.erase(all.begin());

	if (all.size() == 1) {
		fout << "No solution";
		return 0;
	}

	int v = all.size();
	all[v - 1]--;
	all[v - 2]++;

	if (all[v - 2] > all[v - 1]) {
		all[v - 2] += all[v - 1];
		all.erase(--all.end());
	} else {
		while (all[v - 2] * 2 <= all[v - 1]) {
			all.push_back(all[v - 1] - all[v - 2]);
			v = all.size();
			all[v - 2] = all[v - 3];
		}
	}

	fout << n << "=";

	for (int i = 0; i < all.size();i++) {
		fout << all[i];
		if (all.size() - 1 > i) fout << "+";
	}

	fin.close();
	fout.close();
	return 0;
}
