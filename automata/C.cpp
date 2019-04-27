#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int MOD = (int) (1e9 + 7);

size_t n, m, k;
vector<size_t> t;
vector<vector<size_t>> g;

vector<set<size_t>> rev_g;
vector<bool> con_t;

vector<int> color;
vector<size_t> top_sort;

void fill_con() {
    queue<size_t> q;
    for (size_t i = 0; i < k; i++) {
        q.push(t[i]);
        con_t[t[i]] = true;
    }

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();
        for (auto it = rev_g[v].begin(); it != rev_g[v].end(); it++) {
            size_t to = *it;

            if (!con_t[to]) {
                con_t[to] = true;
                q.push(to);
            }
        }
    }
}

bool dfs(size_t v) {
    color[v] = 1;

    for (size_t i = 0; i < g[v].size(); i++) {
        size_t to = g[v][i];
        if (to == 0) continue;

        if (color[to] == 1 && (con_t[v] || con_t[to])) return true;
        if (color[to] == 0 && dfs(to)) return true;
    }
    color[v] = 2;
    top_sort.push_back(v);
    return false;
}

int main() {
    ifstream fin("problem3.in");
    ofstream fout("problem3.out");

    fin >> n >> m >> k;
    t.resize(k);
    g.resize(n + 1, vector<size_t>(26, 0));
    rev_g.resize(n + 1);
    con_t.resize(n + 1, false);
    color.resize(n + 1, 0);

    for (size_t i = 0; i < k; i++) fin >> t[i];

    size_t a, b;
    char c;

    for (size_t i = 0; i < m; i++) {
        fin >> a >> b >> c;
        g[a][c - 'a'] = b;
        rev_g[b].insert(a);
    }

    fill_con();
    if (dfs(1)) {
        fout << -1;
        return 0;
    }
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    for (size_t i = top_sort.size() - 1;; i--) {
        size_t v = top_sort[i];

        for (size_t j = 0; j < g[v].size(); j++) {
            size_t to = g[v][j];
            if (to == 0) continue;

            dp[to] = (dp[to] + dp[v]) % MOD;
        }

        if (i == 0) break;
    }

    int ans = 0;
    for (size_t i = 0; i < k; i++) {
        ans = (ans + dp[t[i]]) % MOD;
    }
    fout << ans;
    return 0;
}
