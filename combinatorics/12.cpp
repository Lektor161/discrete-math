#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> p;

ifstream fin("part2sets.in");
ofstream fout("part2sets.out");

void make_part(int pos, int num) {
	if (pos == n) {
		if (num != k) return;
		vector<vector<int>> un(k);
		for (int i = 0; i < n; i++) un[p[i]].push_back(i + 1);
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < un[i].size(); j++) {
				fout << un[i][j] << " ";
			}
			fout << "\n";
		}
		fout << "\n";
	} else {
		for (int i = 0; i <= num; i++) {
			p[pos] = i;
			if (i == num) make_part(pos + 1, num + 1);
			else make_part(pos + 1, num);
		}
	}
}

int main() {
	fin >> n >> k;
	p.resize(n);
	make_part(0, 0);
	fin.close();
	fout.close();
	return 0;
}