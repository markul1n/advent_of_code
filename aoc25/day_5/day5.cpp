#include "../aoc.cpp"
#include <bits/stdc++.h>

using namespace std;

const int START = 1;
const int END = 0;
const int ID = 2;

void part1() {
  vector<string> lines = readLines();
  vector<pair<ll, int>> events;
  for (string l : lines) {
    if (l.empty())
      continue;
    auto parts = split(l, '-');
    if (parts.size() == 1) {
      events.push_back({stol(parts[0]), ID});
    } else {
      events.push_back({stol(parts[0]), START});
      events.push_back({stol(parts[1]) + 1, END});
    }
  }

  sort(events.begin(), events.end(), [](auto a, auto b) {
    if (a.first != b.first) {
      return a.first < b.first;
    }
    return a.second < b.second;
  });

  ll open = 0;
  ll count = 0;
  for (auto [time, event] : events) {
    if (event == START) {
      open++;
    } else if (event == END) {
      open--;
    } else {
      if (open > 0) {
        count++;
      }
    }
  }
  cout << "part1 : " << count << endl;
}

void part2() {
  vector<string> lines = readLines();
  vector<pair<ll, int>> events;
  for (string l : lines) {
    if (l.empty())
      break;
    auto parts = split(l, '-');
    events.push_back({stol(parts[0]), START});
    events.push_back({stol(parts[1]) + 1, END});
  }

  sort(events.begin(), events.end(), [](auto a, auto b) {
    if (a.first != b.first) {
      return a.first < b.first;
    }
    return a.second < b.second;
  });

  ll open = 0;
  ll count = 0;
  ll start = 0;
  for (auto [time, event] : events) {
    if (event == START) {
      open++;
      if (open == 1) {
        start = time;
      }
    } else {
      open--;
      if (open == 0) {
        count += time - start;
      }
    }
  }
  cout << "part2 : " << count << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
