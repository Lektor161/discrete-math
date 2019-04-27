#include <fstream>

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    string word;
    ifstream fin("problem1.in");
    ofstream fout("problem1.out");
    fin >> word;

    size_t k, n, m, a, b;
    char c;
    fin >> n >> m >> k;

    vector<vector<size_t>> d(n + 1, vector<size_t>(26, 0));
    vector<int> t(k);

    for (size_t i = 0; i < k; i++) {
        fin >> t[i];
    }

    for (size_t i = 0; i < m; i++) {
        fin >> a >> b >> c;
        d[a][c - 'a'] = b;
    }
    size_t cur = 1;
    for (size_t i = 0; i < word.size(); i++) {
        if (d[cur][word[i] - 'a'] == 0) {
            fout << "Rejects";
            return 0;
        }
        cur = d[cur][word[i] - 'a'];
    }
    bool ok = false;
    for (size_t i = 0; i < k; i++) {
        if (t[i] == cur) ok = true;
    }
    if (ok) fout << "Accepts";
    else fout << "Rejects";
}