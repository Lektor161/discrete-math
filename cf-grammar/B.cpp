#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    ifstream fin("epsilon.in");
    ofstream fout("epsilon.out");
    int n, m;
    char s;
    fin >> n >> s;
    string p, word;

    vector<vector<string>> ms(26);
    vector<bool> eps(26);

    getline(fin, p);
    for (int i = 0; i < n; i++) {
        getline(fin, p);
        string right = "";
        bool small = false;
        for (int j = 5; j < p.size(); j++) {
            right += p[j];
            if (p[j] >= 'a' && p[j] <= 'z') small = true;
        }

        if (!small) {
            if (right.size() > 0) {
                ms[p[0] - 'A'].push_back(right);
            } else {
                eps[p[0] - 'A'] = true;
            }
        }
    }
    for (int e = 0; e < 26; e++) {
        for (int i = 0; i < 26; i++) {
            if (eps[i]) continue;
            for (int j = 0; j < ms[i].size(); j++) {
                // check ms[i][j] word, if every eps, eps[i] = true
                bool every = true;
                for (int k = 0; k < ms[i][j].size(); k++) {
                    every &= eps[ms[i][j][k] - 'A'];
                }
                if (every) eps[i] = true;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (eps[i]) fout << (char) ('A' + i) << " ";
    }
    return 0;
}