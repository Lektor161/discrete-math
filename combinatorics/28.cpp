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
vector<int> t(n);

ifstream fin("nextmultiperm.in");
ofstream fout("nextmultiperm.out");

void next(vector<int> a) {
	for (int i = n-2; i >= 0; i--) {
		if (a[i] < a[i + 1]) {
			int l = i + 1;
			for (int j = i + 1; j < n; j++) {
				if (a[j] > a[i]) l = j;
			}
			swap(a[i], a[l]);
			for (int j = 0; j <= i; j++) fout << a[j] << " ";
			for (int j = n - 1; j > i; j--) fout << a[j] << " ";
			return;
		}
	}
	for (int i = 0; i < n; i++) fout << 0 << " ";
}

int main() {
	fin >> n;
	t.resize(n);
	for (int i = 0; i < n; i++) fin >> t[i];

	next(t);
	fout.close();
	fin.close();
}