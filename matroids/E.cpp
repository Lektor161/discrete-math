#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    using elem = std::pair<int, int>;

    std::ifstream fin("cycles.in");
    std::ofstream fout("cycles.out");

    int n, m, col = 0;
    fin >> n >> m;

    int sub = (1 << n);
    std::vector<elem> weight(n);
    std::vector<bool> s(sub, false);

    for (int i = 0; i < n; i++) {
        fin >> weight[i].second;
        weight[i].first = i;
    }

    sort(weight.begin(), weight.end(), [](const elem &lhs, const elem &rhs) {
        return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first);
    });

    for (int i = 0; i < m; i++) {
        fin >> col;
        int hash = 0;
        for (int j = 0; j < col; j++) {
            int e;
            fin >> e;
            hash = (hash | (1 << (--e)));
        }
        s[hash] = true;
    }

    for (int i = 0; i < n; i++) {
        for (int a = 0; a < sub; a++) {
            if (s[a]) continue;
            for (int j = 0; j < n; j++) {
                if ((a & (1 << j)) && s[(a - (1 << j))]) {
                    s[a] = true;
                    break;
                }
            }
        }
    }

    int cur = 0, cost = 0;
    for (elem &e : weight) {
        if (s[cur | (1 << e.first)]) continue;
        cur |= (1 << e.first);
        cost += e.second;

    }
    fout << cost;
}
