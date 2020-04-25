#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <array>

using namespace std;

using ll = uint64_t;
using gen = array<ll, 7>;

ll choose(ll n, ll k) {
    if (k == 0) return 1;
    if (n < 1) return 0;
    ll result = 1;
    for (ll i = n; i <= n + k - 1; i++) {
        result *= i;
    }
    while (k > 1) result /= k, k--;
    return result;
}

struct TComb {
    virtual gen eval() = 0;
};

struct TBaseSet : TComb {
    gen eval() override {
        return {0, 1, 0, 0, 0, 0, 0};
    }
} BSet;

struct TCombSeq : TComb {
    TComb *hs;

    explicit TCombSeq(TComb *sub) : hs(sub) {}

    gen eval() override {
        return {0, 0, 0, 0, 0, 0, 0};
    }
};

struct TCombMultiset : TComb {
    TComb *hs;

    explicit TCombMultiset(TComb *sub) : hs(sub) {}

    gen eval() override {
        return {0, 0, 0, 0, 0, 0, 0};
    }
};

struct TCombPair : TComb {
    TComb *lhs;
    TComb *rhs;

    TCombPair(TComb *l, TComb *r) : lhs(l), rhs(r) {}

    gen eval() override {
        gen a = lhs->eval();
        gen b = rhs->eval();
        gen res{};
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < b.size(); j++) {
                if (i + j < res.size()) res[i + j] += a[i] * b[j];
            }
        }
        return res;
    }
};


string s;
size_t l = 0;
int token = 0;

static const vector<pair<string, int>> tokens = {
        // none = 0
        {"(", 1},
        {")", 2},
        {",", 3},
        {"L", 4},
        {"S", 5},
        {"P", 6},
        {"B", 7}
        // error 8
};

void next_token() {
    while (l < s.size() && s[l] == ' ') l++;
    if (l >= s.size()) {
        token = 0;
        return;
    }
    for (auto t : tokens) {
        size_t i = 0;
        for (; i < t.first.size(); i++) {
            if (l + i == s.size()) break;
            if (t.first[i] != s[l + i]) break;
        }
        if (i == t.first.size()) {
            token = t.second;
            l += t.first.size();
            return;
        }
    }
    token = 8;
}

TComb *parse() {
    next_token();
    assert(token >= 0 && token < 8);
    if (token == 0) return nullptr;
    if (token == 7) return &BSet;
    if (token == 4) {
        l++;
        TComb * tmp = parse();
        l++;
        return new TCombSeq(tmp);
    }
    if (token == 5) {
        l++;
        TComb * tmp = parse();
        l++;
        return new TCombMultiset(tmp);
    }
    next_token();
    vector<TComb *> hs;
    while(token != 2) {
        hs.push_back(parse());
        next_token();
        if (token == 3) continue;
    }
    assert(hs.size() == 2);
    return new TCombPair(hs[0], hs[1]);
}

int main() {
    getline(cin, s);
    TComb *node = parse();
    for (auto t : node->eval()) {
        cout << t << ' ';
    }
}