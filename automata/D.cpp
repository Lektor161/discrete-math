#include <fstream>
#include <vector>
#include <set>

using namespace std;

const int MOD = (int) (1e9 + 7);

int main() {
    ifstream fin("problem4.in");
    ofstream fout("problem4.out");

    size_t n, m, k;
    int l;
    size_t a, b;
    char c;
    fin >> n >> m >> k >> l;

    vector<size_t> t(k);
    vector<vector<size_t>> g(n + 1);
    for (size_t i = 0; i < k; i++) fin >> t[i];

    for (size_t i = 0; i < m; i++) {
        fin >> a >> b >> c;
        g[a].push_back(b);
    }

    set<size_t> on_step;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    on_step.insert(1);

    while (l--) {
        set<size_t> next_step;
        vector<int> next_dp(n + 1, 0);

        for (auto it = on_step.begin(); it != on_step.end(); it++) {
            size_t v = *it;
            for (size_t i = 0; i < g[v].size(); i++) {
                size_t to = g[v][i];

                next_dp[to] = (next_dp[to] + dp[v]) % MOD;
                next_step.insert(to);
            }
        }
        on_step = next_step;
        dp = next_dp;
    }

    int res = 0;
    for (int i = 0; i < k; i++) {
        res = (res + dp[t[i]]) % MOD;
    }

    fout << res;
    return 0;
}
