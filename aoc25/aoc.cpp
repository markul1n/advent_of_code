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

vector<vector<string>> readBlocks() {
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

// --- Printing ---

template <typename S>
std::ostream &operator<<(std::ostream &os, const std::vector<S> &v) {
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
ostream &operator<<(ostream &os, const std::pair<A, B> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// tuple
template <class Tuple, std::size_t... Is>
void print_tuple_impl(ostream &os, const Tuple &t, std::index_sequence<Is...>) {
  ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template <class... Ts>
ostream &operator<<(ostream &os, const std::tuple<Ts...> &t) {
  os << "(";
  print_tuple_impl(os, t, std::index_sequence_for<Ts...>{});
  os << ")";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
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
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
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