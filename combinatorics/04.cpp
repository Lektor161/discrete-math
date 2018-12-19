//#include "stdafx.h"
//#include <iostream>
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

vector<vector<int>> ch;
map <vector<int>, bool> was;

ifstream fin("chaincode.in");
ofstream fout("chaincode.out");

int main()
{
	fin >> n;
	vector<int> a;
	ch.push_back({});
	for (int i = 0; i < n; i++) ch[0].push_back(0);

	was[ch[0]] = true;

	while (true) {
		a = ch.back();
		a.erase(a.begin());
		a.push_back(1);
		if (was[a])  {
			a.back() = 0;
			if (was[a]) break;
		}
		was[a] = true;
		ch.push_back(a);
	}
	for (int i = 0; i < ch.size(); i++) {
		for (int j = 0; j < n; j++) fout << ch[i][j];
		fout << endl;
	}
	fout.close();
	fin.close();
}