#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    size_t k, m;
    cin >> k >> m;
    constexpr int64_t MOD = 1e9 + 7;
    vector<int64_t> c(k), tree(m + 1), kids(m + 1);
    tree[0] = kids[0] = 1;
    for (size_t i = 0; i < k; i++) {
        cin >> c[i];
    }
    sort(c.begin(), c.end());  // cache :)
    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 0; j < k; ++j) {
            if (i >= c[j]) {
                tree[i] = (tree[i] + kids[i - c[j]]) % MOD;
            }
        }
        for (size_t j = 0; j <= i; ++j) {
            kids[i] = (kids[i] + tree[j] * tree[i - j]) % MOD;
        }
    }
    for (size_t i = 1; i <= m; i++) {
        cout << tree[i] << ' ';
    }
}