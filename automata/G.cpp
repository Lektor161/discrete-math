#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main() {
    ifstream fin("equivalence.in");
    ofstream fout("equivalence.out");

    int n1, m1, k1, a, b, t;
    char c;
    fin >> n1 >> m1 >> k1;

    vector<bool> t1(n1 + 1, false);
    for (int i = 0; i < k1; i++) {
        fin >> t;
        t1[t - 1] = true;
    }

    vector<vector<int>> g1(n1 + 1, vector<int>(26, n1));

    for (int i = 0; i < m1; i++) {
        fin >> a >> b >> c;
        g1[a - 1][c - 'a'] = b - 1;
    }

    int n2, m2, k2;
    fin >> n2 >> m2 >> k2;

    vector<bool> t2(n2 + 1, false);
    for (int i = 0; i < k2; i++) {
        fin >> t;
        t2[t - 1] = true;
    }

    vector<vector<int>> g2(n2 + 1, vector<int>(26, n2));

    for (int i = 0; i < m2; i++) {
        fin >> a >> b >> c;
        g2[a - 1][c - 'a'] = b - 1;
    }

    queue<pair<int, int>> q;
    q.push({0, 0});

    map<pair<int, int>, bool> used;

    while (!q.empty()) {
        int v = q.front().first, u = q.front().second;
        q.pop();

        if (t1[v] != t2[u]) {
            fout << "NO";
            return 0;
        }

        used[{v, u}] = true;

        for (int i = 0; i < 26; i++) {
            int z = g1[v][i], x = g2[u][i];

            if (!used[{z, x}]) {
                q.push({z, x});
            }
        }
    }

    fout << "YES";
    return 0;
}