#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
typedef long long int ll;

int n;
vector<char> a;

ifstream fin("brackets.in");
ofstream fout("brackets.out");

void gen(int p, int bal) {
	if(p == n) {
		if (bal) return;
		for (int i = 0; i < n; i++) fout << a[i];
		fout << endl;
	} else {
		a[p] = '(';
		gen(p + 1, bal + 1);
		if (bal) {
			a[p] = ')';
			gen(p + 1, bal - 1);
		}
	}
}

int main() {
	fin >> n;
	n *= 2;
	a.resize(n);
	gen(0, 0);
	fout.close();
	fin.close();
}