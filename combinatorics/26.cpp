//#include "stdafx.h"
#include <fstream>
//#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("nextsetpartition.in");
ofstream fout("nextsetpartition.out");

string c;
int n, k;
vector<vector<int>> a;

void read_line(int p) {
	getline(fin, c);
	int cur = 0;
	for (int i = 0; i < c.length(); i++) {
		if (isdigit(c[i])) {
			cur = 10 * cur + (c[i] - '0');
		}
		else {
			a[p].push_back(cur);
			cur = 0;
		}
	}
	if (cur) a[p].push_back(cur);
}

void next() {
	set<int> dels;
	bool back = false;
	auto e = dels.begin();

	for (int i = k - 1; i >= 0; i--) {
		if (dels.size() && *(--dels.end()) > a[i].back()) {
			//can insert smth to this set
			
			//lets find min ok elem
			e = (--dels.end());
			for (auto it = dels.begin(); it != dels.end(); it++) {
				if (*(it) > a[i].back()) {
					e = it;
					break;
				}
			}
			a[i].push_back(*e);
			dels.erase(e);
			break;
		}

		for (int j = a[i].size() - 1; j >= 0; j--) {
			if (dels.size() && j && *(--dels.end()) > a[i][j]) {
				//can change elem

				//lets find min ok elem
				e = (--dels.end());
				for (auto it = dels.begin(); it != dels.end(); it++) {
					if (*(it) > a[i][j]) {
						e = it;
						break;
					}
				}

				int t = a[i][j];
				a[i][j] = *e;
				dels.erase(e);
				dels.insert(t);
				back = true;
				break;
			}

			dels.insert(a[i][j]);
			a[i].erase((--a[i].end()));
			if (a[i].size() == 0) a.erase(a.begin() + i);
		}
		if (back) break;
		//??
	}

	//min lex tail
	if (dels.empty()) return;
	for (auto it = dels.begin(); it != dels.end(); it++) {
		//a[a.size() - 1].push_back(*it);
		a.push_back({ *it });
	}
}

int main() {
	while (fin >> n >> k) {
		if (n == 0 && k == 0) return 0;
		a.assign(k, {});
		getline(fin, c);
		for (int i = 0; i < k; i++) {
			read_line(i);
		}

		next();

		fout << n << " " << a.size() << endl;
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < a[i].size(); j++) fout << a[i][j] << " ";
			fout << endl;
		}
		fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}