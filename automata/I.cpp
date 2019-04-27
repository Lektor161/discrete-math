#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

ifstream fin("fastminimization.in");
ofstream fout("fastminimization.out");

size_t n, m, k;

vector<bool> t;
vector<vector<size_t>> g;
vector<vector<vector<size_t>>> rev_g;

// answer block

size_t start, n_min;
vector<bool> t_min, checked;
vector<vector<size_t>> g_min;

// end of answer block

void minimize() {
    vector<size_t> set_num(n + 1);
    vector<set<size_t>> cur_set(2);

    for (size_t i = 0; i <= n; i++) {
        set_num[i] = (size_t) t[i];
        cur_set[set_num[i]].insert(i);
    }

    if (cur_set[0].empty()) swap(cur_set[0], cur_set[1]);
    if (cur_set[1].empty()) cur_set.pop_back();

    queue<size_t> q;
    q.push(0);
    if (cur_set.size() == 2) q.push(1);

    while (!q.empty()) {
        size_t cur = q.front();
        q.pop();

        for (int c = 0; c < 26; c++) {
            map<size_t, set<size_t>> involved;

            for (auto it = cur_set[cur].begin(); it != cur_set[cur].end(); it++) {
                for (size_t j = 0; j < rev_g[*it][c].size(); j++) {
                    size_t r = rev_g[*it][c][j];
                    involved[set_num[r]].insert(r);
                }
            }

            for (auto it = involved.begin(); it != involved.end(); it++) {
                size_t key = it->first;
                if (it->second.size() == cur_set[key].size()) continue;


                for (auto ip = it->second.begin(); ip != it->second.end(); ip++) {
                    cur_set[it->first].erase(*ip);
                    set_num[*ip] = cur_set.size();
                }

                if (cur_set[it->first].size() < it->second.size()) {
                    swap(cur_set[it->first], it->second);

                    for (auto ip = cur_set[it->first].begin(); ip != cur_set[it->first].end(); ip++) {
                        set_num[*ip] = it->first;
                    }

                    for (auto ip = it->second.begin(); ip != it->second.end(); ip++) {
                        set_num[*ip] = cur_set.size();
                    }
                }

                q.push(cur_set.size());
                cur_set.push_back(it->second);
            }
        }
    }

    n_min = cur_set.size();

    t_min.resize(n_min + 1, false);
    checked.resize(n_min + 1, false);
    g_min.resize(n_min + 1, vector<size_t>(26, 0));

    for (size_t i = 0; i <= n; i++) {
        if (checked[set_num[i]]) continue;

        for (int j = 0; j < 26; j++) {
            g_min[set_num[i]][j] = set_num[g[i][j]];
        }

        t_min[set_num[i]] = t[i];
        checked[set_num[i]] = true;
    }
    start = set_num[0];
}

struct new_edge {
    size_t from, to;
    char c;

    new_edge(size_t a, size_t b, int q) {
        from = a;
        to = b;
        c = (char) q;
    }
};

int main() {
    fin >> n >> m >> k;

    t.resize(n + 1, false);
    g.resize(n + 1, vector<size_t>(26, n));
    rev_g.resize(n + 1, vector<vector<size_t>>(26));

    size_t a, b;
    char c;

    for (int i = 0; i < k; i++) {
        fin >> a;
        t[a - 1] = true;
    }

    for (int i = 0; i < m; i++) {
        fin >> a >> b >> c;
        g[a - 1][c - 'a'] = b - 1;
    }

    for (size_t i = 0; i < g.size(); i++) {
        for (size_t j = 0; j < 26; j++) {
            rev_g[g[i][j]][j].push_back(i);
        }
    }

    minimize();

    /*fout << n_min << " " << start << endl;
    for (size_t i = 0; i < t_min.size(); i++) {
        if (t_min[i]) fout << i << " ";
    }
    fout << endl << endl;

    for (size_t i = 0; i <= n_min; i++) {
        for (size_t j = 0; j < 26; j++) {
            if (g_min[i][j] != 0) fout << i << " " << j << " " << g_min[i][j] << endl;
        }
    }*/

    // delete trash from automata
    vector<vector<size_t>> rev_edges(n_min);

    for (size_t i = 0; i < n_min; i++) {
        for (size_t j = 0; j < 26; j++) {
            rev_edges[g_min[i][j]].push_back(i);
        }
    }

    vector<bool> connected_s(n_min, false), connected_t(n_min, false);
    connected_s[start] = true;

    queue<size_t> con;
    con.push(start);

    // connected with start
    while (!con.empty()) {
        size_t v = con.front();
        con.pop();

        for (size_t i = 0; i < g_min[v].size(); i++) {
            size_t to = g_min[v][i];
            if (!connected_s[to]) con.push(to);
            connected_s[to] = true;
        }
    }

    // connected with terminals
    for (size_t i = 0; i < t_min.size(); i++) {
        if (t_min[i]) {
            con.push(i);
            connected_t[i] = true;
        }
    }

    while (!con.empty()) {
        size_t v = con.front();
        con.pop();

        for (size_t i = 0; i < rev_edges[v].size(); i++) {
            size_t to = rev_edges[v][i];
            if (!connected_t[to]) con.push(to);
            connected_t[to] = true;
        }
    }

    // transformation from eq classes to min automata
    vector<size_t> num(n_min, 0);
    num[start] = 1;
    size_t cur_num = 2;
    for (size_t i = 0; i < n_min; i++) {
        if (i != start && connected_s[i] && connected_t[i]) num[i] = cur_num++;
    }

    vector<new_edge> edges;
    vector<size_t> t_list;

    for (size_t i = 0; i < n_min; i++) {
        if (num[i] == 0) continue;
        if (t_min[i]) t_list.push_back(num[i]);
        for (size_t j = 0; j < g_min[i].size(); j++) {
            size_t to = g_min[i][j];
            if (num[to] != 0) edges.push_back({num[i], num[to], (char) (j + 'a')});
        }
    }

    fout << cur_num - 1 << " " << edges.size() << " " << t_list.size() << endl;
    for (int i = 0; i < t_list.size(); i++) fout << t_list[i] << " ";
    fout << endl;
    for (int i = 0; i < edges.size(); i++) {
        fout << edges[i].from << " " << edges[i].to << " " << edges[i].c << endl;
    }
}