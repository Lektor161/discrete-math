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
vector<bool> was;
vector<int> a;
ifstream fin("permutations.in");
ofstream fout("permutations.out");

void gen(int p) {
	if(p == n) {
		for (int i = 0; i < n; i++) fout << a[i]+1 << " ";
		fout << endl;
	} else {
		for (int i = 0; i < n; i++) {
			if (!was[i]) {
				was[i] = true;
				a[p] = i;
				gen(p + 1);
				was[i] = false;
			}
		}
	}
}

int main() {
	fin >> n;
	a.resize(n);
	was.resize(n, false);
	gen(0);
	fout.close();
	fin.close();
}