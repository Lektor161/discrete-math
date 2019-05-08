#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int main() {
    ifstream fin("useless.in");
    ofstream fout("useless.out");
    int n;
    char s;
    fin >> n >> s;
    string p;

    vector<vector<string>> ms(26);
    vector<bool> finite(26, false), alpha(26, false);

    alpha[s - 'A'] = true;
    getline(fin, p);
    for (int i = 0; i < n; i++) {
        getline(fin, p);
        string right = "";
        alpha[p[0] - 'A'] = true;
        for (int j = 5; j < p.size(); j++) {
            if (p[j] >= 'A' && p[j] <= 'Z') {
                alpha[p[j] - 'A'] = true;
                right += p[j];
            }
        }
        if (right.size() > 0) {
            ms[p[0] - 'A'].push_back(right);
        } else {
            finite[p[0] - 'A'] = true;
        }
    }

    // reachable
    queue<int> q;
    vector<bool> visited(26, false);

    q.push(s - 'A');
    visited[s - 'A'] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < ms[v].size(); i++) {
            for (int j = 0; j < ms[v][i].size(); j++) {
                int to = ms[v][i][j] - 'A';
                if (!visited[to]) {
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
    }

    // end of reachable

    // generating

    for (int e = 0; e < 26; e++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < ms[i].size(); j++) {
                bool all = true;
                for (int k = 0; k < ms[i][j].size(); k++) {
                    all &= finite[ms[i][j][k] - 'A'];
                }
                if (all) finite[i] = true;
            }
        }
    }

    // end of generating

    // delete trash

    vector<bool> ans(26, false);
    if (finite[s - 'A']) {
        ans[s - 'A'] = true;
        q.push(s - 'A');
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < ms[v].size(); i++) {
            bool all = true;
            for (int j = 0; j < ms[v][i].size(); j++) {
                all &= finite[ms[v][i][j] - 'A'];
            }
            if (!all) continue;

            for (int j = 0; j < ms[v][i].size(); j++) {
                if (!ans[ms[v][i][j] - 'A']) {
                    ans[ms[v][i][j] - 'A'] = true;
                    q.push(ms[v][i][j] - 'A');
                }
            }
        }
    }

    // end of deleting trash

    for (int i = 0; i < 26; i++) {
        if (alpha[i] && (!visited[i] || !finite[i] || !ans[i])) {
            fout << (char) ('A' + i) << " ";
        }
    }
    return 0;
}
/*
7 S
S -> AS
S -> BS
S -> s
E -> EF
E -> FF
A -> a
F -> f
 */