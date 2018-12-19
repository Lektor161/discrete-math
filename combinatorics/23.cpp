#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
typedef long long int ll;

ifstream fin("nextvector.in");
ofstream fout("nextvector.out");

void prev(string p) {
	int ind = -1;
	for (int i = p.length() - 1; i >= 0; i--) {
		if (p[i] == '1') {
			ind = i;
			break;
		}
	}
	if (ind == -1) {
		fout << "-";
		return;
	}

	for (int i = 0; i < p.length(); i++) {
		if (i < ind) fout << p[i];
		if (i == ind) fout << 0;
		if (i > ind) fout << 1;
	}
}

void next(string p) {
	int ind = -1;
	for (int i = p.length() - 1; i >= 0; i--) {
		if (p[i] == '0') {
			ind = i;
			break;
		}
	}

	if (ind == -1) {
		fout << "-";
		return;
	}

	for (int i = 0; i < p.length(); i++) {
		if (i < ind) fout << p[i];
		if (i == ind) fout << 1;
		if (i > ind) fout << 0;
	}
}

int main() {
	string s;
	fin >> s;
	prev(s);
	fout << endl;
	next(s);
	fout.close();
	fin.close();
}