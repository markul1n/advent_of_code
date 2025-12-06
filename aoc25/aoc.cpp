#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <vector>
#include <tuple>
#include <functional>
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
    if (!line.empty() && line.back() == '\r')
      line.pop_back(); // handle CRLF
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

vector<vector<string>> readGrid() {

  auto lines = readLines();
  int R = lines.size();

  vector<vector<string>> grid(R);

  for (int y = 0; y < R; y++) {
    string line = lines[y];
    std::istringstream iss(line);

    std::string word;

    while (iss >> word) {
      grid[y].push_back(word);
    }
  }

  return grid;
}

vector<vector<string>> getBlocks() {
  vector<vector<string>> blocks;
  vector<string> current;

  auto lines = readLines();

  for (const auto &l : lines) {
    if (l.empty()) {
      if (!current.empty()) {
        blocks.push_back(std::move(current));
        current.clear();
      }
    } else {
      current.push_back(l);
    }
  }

  if (!current.empty()) {
    blocks.push_back(std::move(current));
  }

  return blocks;
}
