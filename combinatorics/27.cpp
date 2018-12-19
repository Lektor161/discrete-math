//#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("nextbrackets.in");
ofstream fout("nextbrackets.out");

int main() {
	string s;
	fin >> s;
	int op = 0, cl = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == '(') {
			op++;
			if (cl > op) break;
		}
		else {
			cl++;
		}
	}
	if (cl + op == s.length()) {
		fout << "-";
		return 0;
	}
	for (int i = 0; i < s.length() - cl - op; i++) fout << s[i];
	fout << ")";
	for (int i = 0; i < op; i++)  fout << "(";
	for (int i = 1; i < cl; i++)  fout << ")";
	fin.close();
	fout.close();
	return 0;
}