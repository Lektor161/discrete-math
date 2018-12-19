#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
typedef long long int ll;

ifstream fin("nextchoose.in");
ofstream fout("nextchoose.out");

int main()
{
	int n, k;
	fin >> n >> k;
	vector<int> a(k);
	for (int i = 0; i < k; i++) fin >> a[i];
	a.push_back(n+1);
	for (int i = k - 1; i >= 0; i--) {
		if (a[i + 1] - a[i] > 1) {
			a[i]++;
			for (int j = i + 1; j < k; j++) a[j] = a[j - 1] + 1;
			for (int j = 0; j < k; j++) fout << a[j] << " ";
			return 0;
		}
	}
	fout << -1;
	fout.close();
	fin.close();
}