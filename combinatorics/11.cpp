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
vector<int> a;

ifstream fin("subsets.in");
ofstream fout("subsets.out");

void gen(int p, int fp, int c = 0) {
	if (c) {
		for (int i = 0; i < fp; i++) fout << a[i] << " ";
		fout << endl;
	}

	if(p < n) {
		a[fp] = p + 1;
		gen(p + 1, fp + 1, 1);
		gen(p + 1, fp);
	}
}

int main() {
	fin >> n;
	a.resize(n);
	gen(0, 0, 1);
	fout.close();
	fin.close();
}