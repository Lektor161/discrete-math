#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> answer;

bool ask(int a, int b) {
    cout << "1 " << a << " " << b << endl;
    string ans;
    cin >> ans;
    return (ans == "YES");
}

void printResult() {
    cout << "0 ";
    for (auto t : answer) cout << t << " ";
}

void binsearch(int li, int ri, int val) {
    while (li != ri) {
        int c = (li + ri) / 2;

        if (ask(val, answer[c])) {
            ri = c;
        } else {
            li = c + 1;
        }
    }
    answer.insert(answer.begin() + li, val);
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        binsearch(0, i - 1, i);
    }
    printResult();
}
