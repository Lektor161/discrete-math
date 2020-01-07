#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    using ll = long long int;
    using task = std::pair<int, ll>;

    std::ifstream fin("schedule.in");
    std::ofstream fout("schedule.out");

    int n;
    fin >> n;

    std::vector<task> tasks(n);
    std::set<int> days;

    for (int i = 0; i < n; i++) {
        fin >> tasks[i].first >> tasks[i].second;
        days.insert(i + 1);
    }

    sort(tasks.begin(), tasks.end(), [](const task &lhs, const task &rhs) {
        return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first);
    });

    ll tax = 0;
    for (int i = 0; i < n; i++) {
        auto next = days.lower_bound(tasks[i].first);
        if (*next == tasks[i].first) {
            days.erase(next);
        } else if (next == days.begin()) {
            tax += tasks[i].second;
        } else {
            days.erase(--next);
        }
    }
    fout << tax;
}
