#include <bits/stdc++.h>
#include <ranges>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

const string INPUT_FILE = "input.txt";

vector<string> split(const string &text, char d) {
    vector<string> out;

    for (auto &&part : text | std::views::split(d)) {
        string s(part.begin(), part.end());
        out.push_back(std::move(s));
    }

    return out;
}

vector<string> readLines() {
    ifstream in(INPUT_FILE);
    vector<string> lines;
    string line;

    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // handle CRLF
        lines.push_back(line);
    }

    return lines;
}

string readLine() {
    auto lines = readLines();
    if (lines.empty()) {
        cerr << "Input file is empty\n";
        exit(1);
    }
    return lines[0];
}

