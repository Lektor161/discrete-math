#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::ifstream fin("check.in");
    std::ofstream fout("check.out");

    int n, m, col = 0;
    fin >> n >> m;

    int sub = (1 << n);
    std::vector<int> cnt(sub, 0);
    std::vector<bool> s(sub, false);

    for (int i = 0; i < m; i++) {
        fin >> col;
        int hash = 0;
        for (int j = 0; j < col; j++) {
            int elem;
            fin >> elem;
            hash = (hash | (1 << (--elem)));
        }
        cnt[hash] = col;
        s[hash] = true;
    }

    bool verdict = true;

    if (!s[0]) {
        verdict = false;
    }

    for (int a = 0; a < sub; a++) {
        for (int b = 0; b < sub; b++) {
            if (b != (b & a) || !s[a]) {
                continue;
            }

            if (!s[b]) {
                verdict = false;
            }
        }
    }

    for (int a = 0; a < sub; a++) {
        for (int b = 0; b < sub; b++) {
            if (!s[a] || !s[b] || cnt[a] <= cnt[b]) {
                continue;
            }

            bool any = false;
            int p = a, q = b;
            for (int i = 0; i < n; i++) {
                if ((p & 1) && !(q & 1)) {
                    if (s[(b | ((1 << i)))]) {
                        any = true;
                    }
                }
                p >>= 1;
                q >>= 1;
            }
            if (!any) {
                verdict = false;
            }
        }
    }

    fout << (verdict ? "YES" : "NO");
}
