import std.stdio;
import std.range;
import std.algorithm;
import std.conv;

string escape(string s) {
    string r;
    foreach (char c; s) {
        switch (c) {
            case '\n':
                r ~= "\\n";
                break;
            case '\'':
                r ~= "\\'";
                break;
            case '"':
                r ~= "\\\"";
                break;
            case '\\':
                r ~= "\\\\";
                break;
            default:
                r ~= c;
        }
    }
    return r;
}

string subString(string s, size_t beg, size_t end) {
    return s.dropExactly(beg).take(end - beg).text;
}

string getcode() {
    string s = "import std.stdio;\nimport std.range;\nimport std.algorithm;\nimport std.conv;\n\nstring escape(string s) {\n    string r;\n    foreach (char c; s) {\n        switch (c) {\n            case \'\\n\':\n                r ~= \"\\\\n\";\n                break;\n            case \'\\\'\':\n                r ~= \"\\\\\'\";\n                break;\n            case \'\"\':\n                r ~= \"\\\\\\\"\";\n                break;\n            case \'\\\\\':\n                r ~= \"\\\\\\\\\";\n                break;\n            default:\n                r ~= c;\n        }\n    }\n    return r;\n}\n\nstring subString(string s, size_t beg, size_t end) {\n    return s.dropExactly(beg).take(end - beg).text;\n}\n\nstring getcode() {\n    string s = \"$\";\n    auto pos = countUntil(s, \'$\');\n    return s.subString(0, pos) ~ escape(s) ~ s.subString(pos + 1, s.length);\n}\n\nvoid main() {\n    writef(getcode());\n}";
    auto pos = countUntil(s, '$');
    return s.subString(0, pos) ~ escape(s) ~ s.subString(pos + 1, s.length);
}

void main() {
    writef(getcode());
}
