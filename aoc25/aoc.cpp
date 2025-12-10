#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <cctype>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

const string INPUT_FILE = "input.txt";
const string EXAMPLE    = "example.txt";

void trim(std::string& s) {
    auto not_space = [](unsigned char c){ return !std::isspace(c); };

    // trim right
    s.erase(
        std::ranges::find_if(s | std::views::reverse, not_space).base(),
        s.end());

    // trim left
    s.erase(
        s.begin(),
        std::ranges::find_if(s, not_space));
}

vector<string> split(const string &text, char d) {
  vector<string> out;

  for (auto &&part : text | views::split(d)) {
    string s(part.begin(), part.end());
    out.push_back(move(s));
  }

  return out;
}

// -------------------
// I/O helpers (with optional filename)
// -------------------

vector<string> readLines(const string& filename = INPUT_FILE) {
  ifstream in(filename);
  vector<string> lines;
  string line;

  while (getline(in, line)) {
    trim(line);
    lines.push_back(line);
  }

  while (!lines.empty() && lines.back().empty()) {
    lines.pop_back();
  }

  return lines;
}

string readLine(const string& filename = INPUT_FILE) {
  auto lines = readLines(filename);
  if (lines.empty()) {
    cerr << "Input file is empty: " << filename << "\n";
    exit(1);
  }
  return lines[0];
}

vector<vector<string>> readBlocks(const string& filename = INPUT_FILE) {
  vector<vector<string>> blocks;
  vector<string> current;

  auto lines = readLines(filename);

  for (const auto &l : lines) {
    if (l.empty()) {
      if (!current.empty()) {
        blocks.push_back(move(current));
        current.clear();
      }
    } else {
      current.push_back(l);
    }
  }

  if (!current.empty()) {
    blocks.push_back(move(current));
  }

  return blocks;
}

vector<vector<string>> readGrid(const string& filename = INPUT_FILE) {
  auto blocks = readBlocks(filename);
  auto& lines = blocks.at(0);

  int R = lines.size();
  vector<vector<string>> grid(R);

  for (int y = 0; y < R; y++) {
    string line = lines[y];
    istringstream iss(line);

    string word;
    while (iss >> word) {
      grid[y].push_back(word);
    }
  }

  return grid;
}

// --- Printing ---

template <typename S>
ostream &operator<<(ostream &os, const vector<S> &v) {
  os << "[ ";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i + 1 < v.size())
      os << " , ";
  }
  os << " ]";
  return os;
}

// pair
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// tuple
template <class Tuple, size_t... Is>
void print_tuple_impl(ostream &os, const Tuple &t, index_sequence<Is...>) {
  ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
}

template <class... Ts>
ostream &operator<<(ostream &os, const tuple<Ts...> &t) {
  os << "(";
  print_tuple_impl(os, t, index_sequence_for<Ts...>{});
  os << ")";
  return os;
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{ ";

  auto it = s.begin();
  if (it != s.end()) {
    os << *it;
    ++it;
  }
  for (; it != s.end(); ++it) {
    os << ", " << *it;
  }

  os << " }";
  return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
  os << "{ ";

  auto it = m.begin();
  if (it != m.end()) {
    os << it->first << ": " << it->second;
    ++it;
  }
  for (; it != m.end(); ++it) {
    os << ", " << it->first << ": " << it->second;
  }

  os << " }";
  return os;
}
