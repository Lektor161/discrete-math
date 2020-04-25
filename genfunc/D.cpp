#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <array>

using namespace std;

using ll = int64_t;

std::array<ll, 11> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

ll gcd(ll a, ll b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

pair<ll, ll> add(pair<ll, ll> const &lhs, pair<ll, ll> const &rhs) {
    ll d = lcm(lhs.second, rhs.second);
    pair<ll, ll> res = {0, d};
    res.first = lhs.first * (d / lhs.second) + rhs.first * (d / rhs.second);
    ll e = gcd(res.first, res.second);
    res.first /= e;
    res.second /= e;
    return res;
}

vector<ll> recursive_brace_product(ll const k, ll const i) {
    vector<ll> braces(k);
    vector<ll> ways(k + 1, 0);
    for (ll j = 1; j <= k; j++) {
        braces[j - 1] = j - i;
    }
    ll mask = 0;
    while (mask < (1 << k)) {
        ll prod = 1;
        ll fake = mask;
        size_t cnt = 0;
        for (size_t j = 0; j < k; j++) {
            if (fake % 2) prod *= braces[j], cnt++;
            fake /= 2;
        }
        ways[cnt] += prod;
        mask++;
    }
    return ways;
}

int main() {
    ll r;
    size_t k;
    cin >> r >> k;
    vector<ll> p(k + 1);
    vector<pair<ll, ll>> answ(k + 1, {0, 1});
    for (size_t i = 0; i <= k; i++) cin >> p[i];
    ll pow = 1;
    ll a, b;
    for (size_t i = 0; i <= k; i++) {
        vector<ll> braces = recursive_brace_product(k, i);
        assert(braces.size() == k + 1);
        a = p[i];
        b = pow * fact[k];
        for (size_t j = 0; j <= k; j++) {
            // cout << k << ' ' << i << ' ' << j << ' ' << braces[j] << '\n';
            answ[j] = add(answ[j], {a * braces[j], b});
        }
        pow *= r;
    }
    reverse(answ.begin(), answ.end());
    for (size_t i = 0; i <= k; i++) {
        cout << answ[i].first << '/' << answ[i].second << " ";
    }
}