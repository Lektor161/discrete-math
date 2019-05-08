#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    ifstream fin("automaton.in");
    ofstream fout("automaton.out");
    int n, m;
    char s;
    fin >> n >> s;
    char c, t1, t2;
    string p, word;

    map<pair<char, char>, bool> unary;
    map<pair<char, char>, vector<char>> binary;

    for (int i = 0; i < n; i++) {
        fin >> c >> t1 >> t2 >> p;
        if (p.size() == 2) {
            binary[{c, p[0]}].push_back(p[1]);
        } else {
            unary[{c, p[0]}] = true;
        }
    }

    fin >> m;
    for (int j = 0; j < m; j++) {
        fin >> word;

        set<char> cur;
        cur.insert(s);
        bool res = true, res2 = false;
        for (int i = 0; i < word.size() - 1 && res; i++) {
            set<char> next;
            for (auto it = cur.begin(); it != cur.end(); it++) {
                for (int e = 0; e < binary[{*it, word[i]}].size(); e++) {
                    next.insert(binary[{*it, word[i]}][e]);
                }
            }
            if (next.size() == 0) res = false;
            cur = next;
        }

        for (auto it = cur.begin(); it != cur.end(); it++) {
            res2 |= unary[{*it, word.back()}];
        }

        res &= res2;
        if (res) fout << "yes\n";
        else fout << "no\n";
    }
    return 0;
}