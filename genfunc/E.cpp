#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <array>

using namespace std;

using ll = int64_t;

template<typename T = ll>
struct gen {
private:
    vector<T> func;

public:
    gen() = default;

    explicit gen(size_t n, T val = 0) : func(n, val) {
        assert(n > 0);
    }

    T &operator[](size_t index) {
        return func[index];
    }

    T get(size_t index) const {
        return index < func.size() ? func[index] : 0;
    }

    void reduce() {
        while (func.size() > 1 && func.back() == 0) {
            func.pop_back();
        }
    }

    size_t size() const {
        return func.size();
    }

    void append(T val) {
        func.push_back(val);
    }
};

template<typename T>
gen<T> mul(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    gen<T> res(cnt);
    for (size_t i = 0; i < cnt; i++) {
        for (size_t j = 0; j <= i; j++) {
            res[i] += (lhs.get(j) * rhs.get(i - j));
        }
    }
    // res.reduce();
    return res;
}

template<typename T>
gen<T> div(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    gen<T> res(cnt);
    for (size_t i = 0; i < cnt; i++) {
        res[i] = lhs.get(i);
        for (size_t j = 0; j < i; j++) {
            res[i] -= (res.get(j) * rhs.get(i - j));
        }
        res[i] /= rhs.get(0);
    }
    return res;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, gen<T> const &a) {
    for (size_t i = 0; i < a.size(); i++) {
        s << a.get(i) << ' ';
    }
    return s;
}

vector<ll> recursive_brace_product(ll const r, ll const k) {
    vector<ll> braces(k);
    vector<ll> ways(k + 1, 0);
    for (ll j = 1; j <= k; j++) {
        braces[j - 1] = -r;
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
    ll r, d;
    cin >> r >> d;
    vector<ll> p(d + 1);
    for (size_t i = 0; i <= d; i++) cin >> p[i];

    gen<ll> a(d + 1);
    ll pow_r = 1;
    for (ll i = 0; i <= d; i++) {
        ll pow_i = 1;
        for (ll j = 0; j <= d; j++) {
            a[i] += pow_i * p[j];
            pow_i *= i;
        }
        a[i] *= pow_r;
        pow_r *= r;
    }

    vector<ll> qv = recursive_brace_product(r, d + 1);
    gen<ll> q;
    for (ll t : qv) q.append(t);

    cout << d << '\n' << mul(a, q, d + 1) << '\n';
    cout << d + 1 << '\n' << q;
}
