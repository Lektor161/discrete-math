//#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("telemetry.in");
ofstream fout("telemetry.out");

int main() {
	int n, k,all = 1, j, d=1;
	fin >> n >> k;
	for (int i = 0; i < n; i++) all *= k;
	vector<vector<int>> a(all, vector<int>(n));

	for (int i = 0; i < n; i++) {
		j = 0;
		
		while (j < all) {
			
			for (int t = 0; t < k; t++) {
				for (int e = 0; e < d; e++) {
					a[j][i] = t;
					j++;
				}
			}
			for (int t = k-1; t >= 0; t--) {
				for (int e = 0; e < d && j < all; e++) {
					a[j][i] = t;
					j++;
				}
			}
		}
		d *= k;
	}
	for (int i = 0; i < all; i++) {
		for (int j = 0; j < n; j++) fout << a[i][j];
		fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}