#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int main() {
    size_t k;
    cin >> k;
    int64_t e;
    vector<int64_t> a(k), c(k + 1);
    for (size_t i = 0; i < k; i++) cin >> a[i];
    for (size_t i = 1; i <= k; i++) cin >> e, c[i] = -e;
    c[0] = 1;
    vector<int64_t> p(k, 0);
    for (size_t i = 0; i < p.size(); i++) {
        int64_t sum = 0;
        for (size_t j = 0; j <= i; j++) sum += a[j] * c[i - j];
        p[i] = sum;
    }

    while (p.size() > 1 && p.back() == 0) p.pop_back();
    cout << p.size() - 1 << '\n';
    for (int64_t t : p) cout << t << ' ';
    cout << '\n' << k << "\n";
    for (int64_t t : c) cout << t << ' ';
}