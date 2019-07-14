#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int main() {
    ifstream fin("cf.in");
    ofstream fout("cf.out");
    int n, p;
    char s;
    fin >> n >> s;
    string ru, word;

    vector<vector<string>> ms(26);
    vector<pair<int, string>> rules;
    vector<bool> eps(26, false);
    getline(fin, ru);
    for (int i = 0; i < n; i++) {
        getline(fin, ru);
        string right = "";

        for (int j = 5; j < ru.size(); j++) {
            right += ru[j];
        }

        if (right.empty()) {
            eps[ru[0] - 'A'] = true;
        } else {
            ms[ru[0] - 'A'].push_back(right);
            rules.push_back({ru[0] - 'A', right});
        }
    }
    fin >> word;
    n = (int) word.size();
    p = (int) rules.size();
    vector<vector<vector<bool>>> a(26, vector<vector<bool>>(n + 1, vector<bool>(n + 1, false)));
    vector<vector<vector<vector<bool>>>> h(p);

    for (int i = 0; i < p; i++) {
        h[i].resize(n + 1, vector<vector<bool>>(n + 1, vector<bool>(rules[i].second.size() + 1)));
        for (int j = 0; j <= n; j++) {
            h[i][j][j][0] = true;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (eps[j]) a[j][i][i] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            if (rules[j].second.size() == 1 && rules[j].second[0] == word[i]) {
                a[rules[j].first][i][i + 1] = true;
            }
        }
    }

    for (int len = 0; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            for (int e = 0; e < 26; e++) {
                for (int i = 0; i < p; i++) {
                    for (int k = 1; k <= rules[i].second.size(); k++) {
                        bool ok = false;
                        for (int j = l; j <= r; j++) {
                            if (rules[i].second[k - 1] >= 'A' && rules[i].second[k - 1] <= 'Z') {
                                ok |= (h[i][l][j][k - 1] && a[rules[i].second[k - 1] - 'A'][j][r]);
                            } else {
                                ok |= (h[i][l][j][k - 1] && r - j == 1 && word[j] == rules[i].second[k - 1]);
                            }
                        }
                        if (ok) h[i][l][r][k] = true;
                    }
                }

                for (int i = 0; i < p; i++) {
                    if (h[i][l][r][rules[i].second.size()]) {
                        a[rules[i].first][l][r] = true;
                    }
                }
            }
        }
    }

    if (a[s - 'A'][0][n]) fout << "yes";
    else fout << "no";
    return 0;
}
