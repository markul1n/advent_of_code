#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

const string INPUT_FILE = "input.txt";
const string EXAMPLE = "example.txt";

void trim(std::string &s) {
  auto not_space = [](unsigned char c) { return !std::isspace(c); };

  // trim right
  s.erase(std::ranges::find_if(s | std::views::reverse, not_space).base(),
          s.end());

  // trim left
  s.erase(s.begin(), std::ranges::find_if(s, not_space));
}

vector<string> split(const string &text, char d) {
  vector<string> out;

  for (auto &&part : text | views::split(d)) {
    string s(part.begin(), part.end());
    out.push_back(std::move(s));
  }

  return out;
}

vector<string> splitRegex(const string &text, const string &pattern) {
  vector<string> out;
  regex regex_pattern(pattern);

  sregex_token_iterator iter(text.begin(), text.end(), regex_pattern, -1);
  sregex_token_iterator end;

  for (; iter != end; ++iter) {
    string s = *iter;
    trim(s);
    if (!s.empty()) {
      out.push_back(s);
    }
  }

  return out;
}

// -------------------
// I/O helpers (with optional filename)
// -------------------

vector<string> readLines(const string &filename = INPUT_FILE) {
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

vector<int> parseInts(const string &line) {
  vector<int> ints;
  auto nums = splitRegex(line, "\\D+");
  for (string num : nums) {
    trim(num);
    if (num.empty())
      continue;
    ints.push_back(stoi(num));
  }

  return ints;
}

vector<ll> parseLongs(const string &line) {
  vector<ll> longs;
  auto nums = splitRegex(line, "\\D+");
  for (string num : nums) {
    trim(num);
    if (num.empty())
      continue;
    longs.push_back(stol(num));
  }

  return longs;
}

string readLine(const string &filename = INPUT_FILE) {
  auto lines = readLines(filename);
  if (lines.empty()) {
    cerr << "Input file is empty: " << filename << "\n";
    exit(1);
  }
  return lines[0];
}

vector<vector<string>> readBlocks(const string &filename = INPUT_FILE) {
  vector<vector<string>> blocks;
  vector<string> current;

  auto lines = readLines(filename);

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

vector<vector<string>> readGrid(const string &filename = INPUT_FILE) {
  auto blocks = readBlocks(filename);
  auto &lines = blocks.at(0);

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

template <class... Ts> ostream &operator<<(ostream &os, const tuple<Ts...> &t) {
  os << "(";
  print_tuple_impl(os, t, index_sequence_for<Ts...>{});
  os << ")";
  return os;
}

template <typename Iterator>
void print_range(std::ostream &os, Iterator begin, Iterator end,
                 const std::string &sep = ", ") {
  if (begin == end)
    return;
  os << *begin;
  ++begin;
  for (; begin != end; ++begin) {
    os << sep << *begin;
  }
}

template <typename S>
std::ostream &operator<<(std::ostream &os, const std::vector<S> &v) {
  os << "[ ";
  print_range(os, v.begin(), v.end(), " , ");
  os << " ]";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
  os << "{ ";
  print_range(os, s.begin(), s.end());
  os << " }";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &s) {
  os << "{ ";
  print_range(os, s.begin(), s.end());
  os << " }";
  return os;
}

template <typename Iterator>
void print_map_range(std::ostream &os, Iterator begin, Iterator end,
                     const std::string &sep = ", ") {
  if (begin == end)
    return;
  os << begin->first << ": " << begin->second;
  ++begin;
  for (; begin != end; ++begin) {
    os << sep << begin->first << ": " << begin->second;
  }
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
  os << "{ ";
  print_map_range(os, m.begin(), m.end());
  os << " }";
  return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &m) {
  os << "{ ";
  print_map_range(os, m.begin(), m.end());
  os << " }";
  return os;
}
