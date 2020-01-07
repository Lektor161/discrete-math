//#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> g;
vector<pair<int, int>> weight;
vector<int> visited, par, ans;

bool dfs(int v) {
    if (visited[v]) return false;
    visited[v] = 1;
    for (auto to : g[v]) {
        if (par[to] == -1 || dfs(par[to])) {
            par[to] = v;
            ans[v] = to;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");

    int n = 0, col = 0, a = 0, w = 0;
    fin >> n;
    g.resize(n);
    visited.resize(n, 0);
    par.resize(n, -1);
    ans.resize(n, -1);

    for (int i = 0; i < n; i++) {
        fin >> w;
        weight.emplace_back(w, i);
    }
    sort(weight.rbegin(), weight.rend());

    for (int i = 0; i < n; i++) {
        fin >> col;
        for (int j = 0; j < col; j++) {
            fin >> a;
            g[i].push_back(--a);
        }
    }
    for (int i = 0; i < n; i++) {
        dfs(weight[i].second);
        visited.assign(n, 0);
    }

    for (int to : ans) {
        fout << to + 1 << " ";
    }
}