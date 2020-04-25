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

    T operator[](size_t index) const {
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
gen<T> operator*(gen<T> const &lhs, gen<T> const &rhs) {
    size_t n = lhs.size(), m = rhs.size();
    gen<T> res(n + m + 3);
    for (int i = 0; i <= n + m + 2; i++) {
        for (int j = 0; j <= i; ++j) {
            res[i] = (res[i] + lhs[j] * rhs[i - j]) % MOD;
        }
    }
    return res;
}

template<typename T>
gen<T> div(gen<T> const &lhs, gen<T> const &rhs, size_t cnt = 1000) {
    size_t n = lhs.size(), m = rhs.size();
    gen<T> res(1000);
    for (int i = 0; i < 1000; ++i) {
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
        s << a[i] << ' ';
    }
    return s;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    gen<int64_t> p(n + 1), q(m + 1);
    for (size_t i = 0; i <= n; i++) cin >> p[i];
    for (size_t i = 0; i <= m; i++) cin >> q[i];

    gen addd = p + q;
    addd.reduce();
    cout << addd.size() << '\n' << addd << '\n';

    gen mulll = p * q;
    mulll.reduce();
    cout << mulll.size() << '\n' << mulll << '\n';

    gen divvv = div(p, q);
    for (size_t i = 0; i < 1000; i++) cout << divvv[i] << " ";
}
