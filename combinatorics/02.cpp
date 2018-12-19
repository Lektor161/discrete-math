//#include "stdafx.h"
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

ifstream fin("gray.in");
ofstream fout("gray.out");

void maddde(int p) {
	for (int i = 0; i < n; i++) {
		a[i] = p % 2;
		p /= 2;
	}
	for (int i = n - 1; i >= 0; i--) fout << a[i];
	fout << endl;
}

int main()
{
	fin >> n;
	a.resize(n);
	for (int i = 0; i < (1<<n); i++) {
		maddde(i ^ (i >> 1));
	}
	fout.close();
	fin.close();
}