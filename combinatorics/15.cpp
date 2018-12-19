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

int main()
{
	ifstream fin("num2choose.in");
	ofstream fout("num2choose.out");
	vector<vector<ll>> c_table(31, vector<ll>(31, 0));
	c_table[0][0] = 1;
	for (int i = 1; i < 31; i++) {
		c_table[i][0] = 1;
		for (int j = 1; j < 31; j++) {
			c_table[i][j] += c_table[i - 1][j] + c_table[i - 1][j - 1];
		}
	}

	int n, k, m;
	fin >> n >> k >> m;
	m++;
	int l = 0;
	for (int i = 1; i <= k; i++) {
		for (; l < n; l++) {
			if (m > c_table[n - l - 1][k - i]) m -= c_table[n - l - 1][k - i];
			else {
				fout << ++l << " ";
				break;
			}
		}
	}
	fout.close();
	fin.close();
}