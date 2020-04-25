#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
using ll = int64_t;

constexpr ll MOD = 998244353;

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
            res[i] += (lhs.get(j) * rhs.get(i - j)) % MOD;
            res[i] %= MOD;
            if (res[i] < 0) res[i] += MOD;
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
            res[i] -= (res.get(j) * rhs.get(i - j)) % MOD;
            res[i] %= MOD;
            if (res[i] < 0) res[i] += MOD;
        }
        res[i] /= rhs.get(0);
    }
    return res;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, gen<T> const &a) {
    for (size_t i = 0; i < a.size(); i++) {
        s << a.get(i) << '\n';
    }
    return s;
}

int main() {
    size_t k, n;
    cin >> k >> n;

    vector<vector<ll>> choose(k + 1, vector<ll>(k + 1));
    for (size_t i = 0; i <= k; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (size_t j = 1; j < i; j++) {
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % MOD;
            if (choose[i][j] < 0) choose[i][j] += MOD;
        }
    }

    /*
     * THANK YOU OEIS
     *
     * https://oeis.org/A211216
     * http://faculty.valpo.edu/lpudwell/slides/notredame.pdf
     *
     */

    gen lhs(k), rhs(k);
    const ll sign[] = {1, -1};
    for (size_t i = 0; i + i + 2 <= k; i++) {
        lhs[i] = choose[k - i - 2][i] * sign[(i & 1)];
    }
    for (size_t i = 0; i + i + 1 <= k; i++) {
        rhs[i] = choose[k - i - 1][i] * sign[(i & 1)];
    }
    cout << div(lhs, rhs, n);
}