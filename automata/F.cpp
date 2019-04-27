#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

vector<bool> t1, t2, visited;
vector<vector<int>> g1, g2;

bool dfs(int v1, int v2) {
    visited[v1] = true;

    if (t1[v1] != t2[v2]) return false;

    bool res = true;
    for (int i = 0; i < 26; i++) {
        int z = g1[v1][i], x = g2[v2][i];

        if ((z == 0 && x != 0) || (z != 0 && x == 0)) return false;

        if (!visited[z]) res &= dfs(z, x);
    }
    return res;
}

int main() {
    ifstream fin("isomorphism.in");
    ofstream fout("isomorphism.out");

    int n1, m1, k1, a, b, t;
    char c;
    fin >> n1 >> m1 >> k1;

    t1.resize(n1 + 1, false);
    visited.resize(n1 + 1, false);
    g1.resize(n1 + 1, vector<int>(26, 0));

    for (int i = 0; i < k1; i++) {
        fin >> t;
        t1[t] = true;
    }

    for (int i = 0; i < m1; i++) {
        fin >> a >> b >> c;
        g1[a][c - 'a'] = b;
    }

    int n2, m2, k2;
    fin >> n2 >> m2 >> k2;

    t2.resize(n2 + 1, false);
    g2.resize(n2 + 1, vector<int>(26, 0));

    for (int i = 0; i < k2; i++) {
        fin >> t;
        t2[t] = true;
    }

    for (int i = 0; i < m2; i++) {
        fin >> a >> b >> c;
        g2[a][c - 'a'] = b;
    }

    if (dfs(1, 1)) fout << "YES";
    else fout << "NO";
    return 0;
}