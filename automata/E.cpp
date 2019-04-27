#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

const int MOD = (int) (1e9 + 7);

int main() {
    ifstream fin("problem5.in");
    ofstream fout("problem5.out");

    int l;
    size_t n, m, k;
    fin >> n >> m >> k >> l;
    vector<size_t> t(k);
    for (size_t i = 0; i < k; i++) fin >> t[i];

    size_t a, b;
    char c;

    vector<vector<vector<size_t>>> g(n + 1, vector<vector<size_t>>(26));
    for (size_t i = 0; i < m; i++) {
        fin >> a >> b >> c;
        g[a][c - 'a'].push_back(b);
    }

    // Tompson algo start

    map<vector<bool>, size_t> qd;
    queue<vector<bool>> p;
    vector<bool> tmp(n + 1, false);
    tmp[1] = true;
    qd[tmp] = 1;
    p.push(tmp);

    vector<vector<size_t>> dka_g(2);
    vector<size_t> dka_t;

    while (!p.empty()) {
        vector<bool> pd = p.front();
        p.pop();

        bool flag = false;
        for (size_t i = 0; i < k; i++) {
            if (pd[t[i]]) flag = true;
        }
        if (flag) dka_t.push_back(qd[pd]);

        for (size_t i = 0; i < 26; i++) {
            tmp.assign(n + 1, false);

            for (size_t j = 1; j <= n; j++) {
                if (!pd[j]) continue;

                for (size_t e = 0; e < g[j][i].size(); e++) {
                    tmp[g[j][i][e]] = true;
                }
            }

            if (qd[tmp] == 0) {
                qd[tmp] = qd.size();
                p.push(tmp);
            }

            if (dka_g.size() == qd.size()) dka_g.push_back({});

            dka_g[qd[pd]].push_back(qd[tmp]);
        }
    }

    // Tompson algo end

    n = qd.size();
    set<size_t> on_step;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    on_step.insert(1);

    while (l--) {
        set<size_t> next_step;
        vector<int> next_dp(n + 1, 0);

        for (auto it = on_step.begin(); it != on_step.end(); it++) {
            size_t v = *it;
            for (size_t i = 0; i < dka_g[v].size(); i++) {
                size_t to = dka_g[v][i];

                next_dp[to] = (next_dp[to] + dp[v]) % MOD;
                next_step.insert(to);
            }
        }
        on_step = next_step;
        dp = next_dp;
    }

    int ans = 0;

    for (size_t i = 0; i < dka_t.size(); i++) {
        ans = (ans + dp[dka_t[i]]) % MOD;
    }
    fout << ans;
    return 0;
}