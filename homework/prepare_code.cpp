#include <iostream>
#include <string>

using namespace std;

string escape(string const &s) {
    string result;
    for (char c : s) {
        switch (c) {
            case '\n':
                result += "\\n";
                break;
            case '\'':
                result += "\\'";
                break;
            case '"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            default:
                result += c;
        }
    }
    return result;
}

int main() {
    string s;
    char c;
    while (!feof(stdin)) {
        c = getchar();
        if (!feof(stdin)) s += c;
    }
    cout << escape(s);
}

