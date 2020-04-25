#include <iostream>

#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

constexpr int64_t MOD = 998244353;

template<typename T>
struct gen {
private:
    vector<T> func;

public:
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
        return func.size() - 1;
    }
};

int64_t binpow(int64_t val, int64_t pow) {
    if (pow == 0) return 1;
    if (pow == 1) return val;

    if (pow % 2) {
        return (val * binpow(val, pow - 1)) % MOD;
    } else {
        int64_t part = binpow(val, pow / 2);
        return (part * part) % MOD;
    }
}

int64_t fast_reverse(int64_t val) {
    return binpow(val, MOD - 2);
}

int64_t choose(int64_t n) {
    int64_t a = 1, b = 1;
    for (int i = 0; i <= n - 1; ++i) {
        a *= (1 - 2 * i + MOD);
        a %= MOD;
        b *= ((i + 1) * 2) % MOD;
        b %= MOD;
    }
    return (a * fast_reverse(b)) % MOD;
}

template<typename T>
gen<T> operator+(gen<T> const &lhs, gen<T> const &rhs) {
    size_t n = lhs.size(), m = rhs.size();
    gen<T> res(max(n, m) + 1);
    for (size_t i = 0; i <= n || i <= m; i++) {
        res[i] = (lhs[i] + rhs[i]) % MOD;
    }
    return res;
}

template<typename T>
gen<T> mul(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    size_t n = lhs.size(), m = rhs.size();
    size_t s = min(n + m + 3, cnt);
    gen<T> res(s);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j <= i; ++j) {
            res[i] += (lhs.get(j) * rhs.get(i - j)) % MOD;
            res[i] %= MOD;
        }
    }
    res.reduce();
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
    for (int i = 0; i < cnt; ++i) {
        res[i] = lhs[i];
        for (int j = 0; j < i; ++j) {
            res[i] -= (res[j] * rhs[i - j]) % MOD;
            if (res[i] < 0) res[i] += MOD;
        }
        res[i] /= rhs[0];
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

int main() {
    size_t n, m;
    cin >> n >> m;
    gen<int64_t> p(n + 1), sqrt(m), exp(m), ln(m), step(1, 1);
    for (size_t i = 0; i <= n; i++) cin >> p[i];
    sqrt[0] = exp[0] = 1;
    int64_t factorial = 1, log = MOD - 1;
    for (int i = 1; i < m; ++i) {
        step = mul(step, p, m);
        factorial = (factorial * i) % MOD;
        log = MOD - log;
        for (int j = 0; j < m; ++j) {
            int64_t ee = step.get(j);
            sqrt[j] = (sqrt[j] + choose(i) * ee) % MOD;
            exp[j] = (fast_reverse(factorial) % MOD * ee + exp[j]) % MOD;
            ln[j] = ((log * fast_reverse(i)) % MOD * ee + ln[j]) % MOD;
        }
    }
    cout << sqrt << '\n' << exp << '\n' << ln;
}