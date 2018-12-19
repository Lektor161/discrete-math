//#include "stdafx.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long int ll;
typedef long double ld;

int main()
{
	ifstream fin("num2perm.in");
	ofstream fout("num2perm.out");
	int n, r; ll p, t;
	fin >> n >> p;
	//p--;
	vector<int> por(n + 1);
	vector<ll> f(n + 1, 1);
	for (int i = 2; i <= n; i++) f[i] = f[i - 1] * i;
	for (int i = 0; i <= n; i++) por[i] = i - 1;

	for (int i = 1; i <= n; i++) {
		t = p / f[n - i];
		p -= t * f[n - i];
		for (int j = 0; j <= n; j++) {
			if (por[j] == t) {
				r = j;
				por[j] = -1;
				break;
			}
		}
		for (int j = r + 1; j <= n; j++) por[j]--;
		fout << r << " ";
	}
	fout.close();
	fin.close();
}