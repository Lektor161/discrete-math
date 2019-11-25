#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

ifstream fin("guyaury.in");
ofstream fout("guyaury.out");

vector<int> answer;
vector<vector<bool>> g;

bool ask(int a, int b) {
    return g[a - 1][b - 1];
}

void printResult() {
    for (auto t : answer) fout << t << " ";
}

void binsearch(int li, int ri, int val) {
    while (li != ri) {
        int c = (li + ri) / 2;

        if (ask(val, answer[c])) {
            ri = c;
        } else {
            li = c + 1;
        }
    }
    answer.insert(answer.begin() + li, val);
}

void makeCycle(int k, int n) {
    bool cycle = false;
    while (!cycle) {
        cycle = true;
        for (int i = k + 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                if (!ask(answer[i], answer[j])) continue;

                vector<int> buffer(answer.begin() + k + 1, answer.begin() + i + 1);

                for (int t = 0; t >= j - k; t--) {
                    answer[t + i] = answer[t + k];
                }
                for (int t = 0; t < i - k; t++) {
                    answer[t + j] = buffer[t];
                }

                k = i;
                cycle = false;
                break;
            }
            if (!cycle) break;
        }
    }
}

int main() {
    int n;
    fin >> n;
    g.resize(n, vector<bool>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            char t;
            fin >> t;
            if (t == '1') {
                g[i][j] = true;
                g[j][i] = false;
            } else {
                g[i][j] = false;
                g[j][i] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        binsearch(0, i - 1, i);
    }

    assert(answer.size() == n);
    /*
     * hamiltonian path here, make cycle
     * https://codeforces.com/blog/entry/61402
     */

    int k = n - 1;
    while (k > 0 && !ask(answer[k], answer[0])) k--;

    if (k != n - 1) makeCycle(k, n);
    printResult();
}
