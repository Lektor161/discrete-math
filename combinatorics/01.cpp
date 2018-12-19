#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;

ifstream fin("allvectors.in");
ofstream fout("allvectors.out");

void maddde(int p) {
	if (p == n) {
		for (int i = 0; i< n; i++) fout << a[i];
		fout << endl;
	} else {
		a[p] = 0;
		maddde(p + 1);
		a[p] = 1;
		maddde(p + 1);
	}
}

int main() {
	fin >> n;
	a.resize(n);
	maddde(0);
	fout.close();
	fin.close();
}