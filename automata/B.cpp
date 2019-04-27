#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream fin("problem2.in");
    ofstream fout("problem2.out");
    string word;
    fin >> word;

    size_t k, n, m, a, b, q;
    char c;
    fin >> n >> m >> k;

    vector<vector<vector<size_t>>> d(n + 1, vector<vector<size_t>>(26));
    map<size_t, bool> t;

    for (size_t i = 0; i < k; i++) {
        fin >> q;
        t.insert({q, true});
    }

    for (size_t i = 0; i < m; i++) {
        fin >> a >> b >> c;
        d[a][c - 'a'].push_back(b);
    }

    vector<vector<bool>> dp(word.size(), vector<bool>(n + 1, false));

    for (size_t j = 1; j <= n; j++) {
        for (size_t i = 0; i < d[j][word.back() - 'a'].size(); i++) {
            if (t[d[j][word.back() - 'a'][i]]) {
                dp[word.size() - 1][j] = true;
            }
        }
    }

    for (size_t i = word.size() - 2; i >= 0; i--) {
        for (size_t j = 1; j <= n; j++) {
            //dp[i][j] = ?
            for (size_t w = 0; w < d[j][word[i] - 'a'].size(); w++) {
                size_t to = d[j][word[i] - 'a'][w];
                if (dp[i + 1][to]) dp[i][j] = true;
            }
        }

        if (i == 0) break;
    }
    fout << (dp[0][1] ? "Accepts" : "Rejects");
}