#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    ifstream fin("chvatal.in");
    ofstream fout("chvatal.out");

    int n;
    fin >> n;

    vector<int> cycle(n);
    vector<vector<bool>> g(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        cycle[i] = i;
        for (int j = 0; j < i; j++) {
            char t;
            fin >> t;
            if (t == '1') {
                g[i][j] = true;
                g[j][i] = true;
            }
        }
    }
    for (int i = 0; i < n * n; i++) {
        int a = cycle[i];
        int b = cycle[i + 1];
        if (!g[a][b]) {
            int bound = i + 2;
            while (bound + 1 < cycle.size()) {
                if (g[a][cycle[bound]] && g[b][cycle[bound + 1]]) {
                    break;
                }
                bound++;
            }

            if (bound + 1 == cycle.size()) {
                bound = i + 2;
                while (bound < cycle.size() && !g[a][cycle[bound]]) bound++;
            }

            reverse(cycle.begin() + i + 1, cycle.begin() + bound + 1);
        }
        cycle.push_back(a);
    }

    assert(cycle.size() == n * n + n);
    for (int i = n * n; i < cycle.size(); i++) {
        fout << cycle[i] + 1 << " ";
    }
}
