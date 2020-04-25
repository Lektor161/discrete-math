#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

constexpr int64_t MOD = 104857601;

template<typename T = int64_t>
struct gen {
    vector<T> func;

public:
    explicit gen(size_t n, T val = 0) : func(n, val) {
        assert(n > 0);
    }

    T &operator[](size_t index) {
        return func[index];
    }

    /*T operator[](size_t index) const {
        return func[index];
    }*/

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

    typename vector<T>::iterator begin() {
        return func.begin();
    }

    typename vector<T>::iterator end() {
        return func.end();
    }
};

template<typename T>
gen<T> operator+(gen<T> const &lhs, gen<T> const &rhs) {
    size_t n = lhs.size(), m = rhs.size();
    gen<T> res(max(n, m) + 1);
    for (size_t i = 0; i <= n || i <= m; i++) {
        res[i] = (lhs.get(i) + rhs.get(i)) % MOD;
    }
    return res;
}

template<typename T>
gen<T> mul(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    size_t n = lhs.size(), m = rhs.size();
    size_t s = min(n + m + 3, cnt);
    gen<T> res(s);
    for (size_t i = 0; i < s; i += 2) {  // TRICK
        for (size_t j = 0; j <= i; ++j) {
            res[i] += (lhs.get(j) * rhs.get(i - j)) % MOD;
            res[i] %= MOD;
        }
    }
    // res.reduce();
    return res;
}

template<typename T>
gen<T> operator*(gen<T> const &lhs, gen<T> const &rhs) {
    return mul(lhs, rhs, lhs.size() + rhs.size() + 3);
}

template<typename T>
gen<T> div(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    size_t n = lhs.size(), m = rhs.size();
    gen<T> res(cnt);
    for (size_t i = 0; i < cnt; ++i) {
        res[i] = lhs.get(i);
        for (size_t j = 0; j < i; ++j) {
            res[i] -= (res[j] * rhs.get(i - j)) % MOD;
            if (res[i] < 0) res[i] += MOD;
        }
        res[i] /= rhs.get(0);
    }
    return res;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, gen<T> const &a) {
    for (size_t i = 0; i <= a.size(); i++) {
        s << a.get(i) << ' ';
    }
    return s;
}

int64_t neg(int64_t val) {
    return (val ? MOD - val : 0);
}

int main() {
    size_t k;
    int64_t n;
    cin >> k >> n;
    gen p(2 * k), c(k), q(k + 1), negq(k + 1);
    q[0] = 1, n--;
    for (size_t i = 0; i < k; i++) cin >> p[i], assert(p[i] > 0);
    for (size_t i = 0; i < k; i++) cin >> c[i], q[i + 1] = neg(c[i]), assert(c[i] > 0);

    /*
     * THANK YOU ANDREW STANKEVICH
     * https://www.youtube.com/watch?v=vegQZ4NG0ms&list=PLk-kd1TpYlH6W4RBNSu8Iv_ISbt4gp7hd&index=2
     */

    while (n >= k) {
        fill(p.begin() + k, p.end(), 0);
        for (size_t i = k; i < 2 * k; ++i) {
            for (size_t j = 1; j <= k; ++j) {
                p[i] = (p[i] - q[j] * p[i - j]) % MOD;
                if (p[i] < 0) p[i] += MOD;
            }
        }
        for (size_t i = 0; i <= k; i += 2) {
            negq[i] = q[i];
            if (i + 1 <= k) negq[i + 1] = neg(q[i + 1]);
        }
        gen pr = q * negq;
        for (size_t i = 0; i <= k; i++) q[i] = pr[i * 2];
        for (size_t i = n % 2; i < 2 * k; i += 2) p[i / 2] = p[i];
        n = n / 2;
    }
    cout << p[n];
}