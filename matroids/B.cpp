#include <fstream>
#include <vector>
#include <algorithm>

typedef long long int ll;

std::vector<int> val, parent;

struct edge {
    ll weight;
    int s, f;
    int index;
};

int find_set(int a) {
    if (parent[a] == a) return a;
    parent[a] = find_set(parent[a]);
    return parent[a];
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return;
    if (val[a] > val[b]) std::swap(a, b);
    parent[a] = b;
    val[b] += val[a];
}

int main() {
    std::ifstream fin("destroy.in");
    std::ofstream fout("destroy.out");

    int n, m, a, b;
    ll s, c, cur_cost = 0;
    edge t;
    fin >> n >> m >> s;
    val.resize(n, 1);
    parent.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    std::vector<edge> rebra(m);
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> c;
        t.weight = c;
        t.s = std::min(a, b) - 1;
        t.f = std::max(a, b) - 1;
        t.index = i + 1;
        rebra[i] = t;
    }
    sort(rebra.begin(), rebra.end(),
         [](const edge &a, const edge &b) { return a.weight > b.weight; });

    std::vector<edge> unused;
    std::vector<int> answer;

    for (int i = 0; i < m; i++) {
        if (find_set(rebra[i].s) != find_set(rebra[i].f)) {
            union_set(rebra[i].s, rebra[i].f);
        } else {
            unused.push_back(rebra[i]);
        }
    }
    reverse(unused.begin(), unused.end());

    for (edge &e : unused) {
        if (cur_cost + e.weight <= s) {
            cur_cost += e.weight;
            answer.push_back(e.index);
        }
    }
    sort(answer.begin(), answer.end());
    fout << answer.size() << "\n";
    for (auto ind : answer) {
        fout << ind << " ";
    }
}
