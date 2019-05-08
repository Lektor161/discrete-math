#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MOD = (int) (1e9 + 7);

int main() {
    ifstream fin("nfc.in");
    ofstream fout("nfc.out");
    int n;
    char s;
    fin >> n >> s;
    char c, t1, t2;
    string p, word;

    map<int, vector<pair<int, int>>> binary;
    vector<vector<int>> unary(26, vector<int>(26, 0));

    for (int i = 0; i < n; i++) {
        fin >> c >> t1 >> t2 >> p;
        if (p.size() == 2) {
            binary[c - 'A'].push_back({p[0] - 'A', p[1] - 'A'});
        } else {
            unary[c - 'A'][p[0] - 'a']++;
        }
    }

    fin >> word;
    n = (int) word.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(26, 0)));

    for (int i = 0; i < n; i++) {
        // dp[i][i][c]
        for (int j = 0; j < 26; j++) {
            if (unary[j][word[i] - 'a']) dp[i][i][j] += unary[j][word[i] - 'a'];
            dp[i][i][j] %= MOD;
        }
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int l = 0; l < n - i; l++) {
            int r = l + i;
            for (int m = l; m < r; m++) {
                for (int c = 0; c < 26; c++) {
                    for (int j = 0; j < binary[c].size(); j++) {
                        int to1 = binary[c][j].first, to2 = binary[c][j].second;
                        dp[l][r][c] += (1ll * dp[l][m][to1] * dp[m + 1][r][to2]) % MOD;
                        dp[l][r][c] %= MOD;
                    }
                }
            }
        }
    }
    fout << dp[0][n - 1][s - 'A'];
    return 0;
}