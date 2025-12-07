#include "../aoc.cpp"
#include <bits/stdc++.h>

using namespace std;

const char SPLITTER = '^';
const char BEAM = 'S';
const char EMPTY = '.';

void part1() {
  auto lines = readLines();
  int R = lines.size();
  int C = lines.at(0).size();

  int cnt = 0;

  for (int y = 1; y < R; y++) {
    for (int x = 0; x < C; x++) {
      if (lines[y - 1][x] == BEAM) {
        if (lines[y][x] == SPLITTER) {
          cnt++;
          if (x - 1 >= 0) {
            lines[y][x - 1] = BEAM;
          }
          if (x + 1 < C) {
            lines[y][x + 1] = BEAM;
          }
        } else {
          lines[y][x] = BEAM;
        }
      }
    }
  }

  cout << cnt << endl;
}

void part2() {
  auto lines = readLines();

  int R = lines.size();
  int C = lines.at(0).size();

  vector<vector<ll>> dp(R + 1, vector<ll>(C));

  for (int y = R - 1; y >= 0; y--) {
    for (int x = 0; x < C; x++) {
      if (lines[y][x] == SPLITTER) {
        dp[y][x] = 1;

        if (x - 1 >= 0) {
          dp[y][x] += dp[y + 1][x - 1];
        }
        if (x + 1 < C) {
          dp[y][x] += dp[y + 1][x + 1];
        }
      } else {
        dp[y][x] = dp[y + 1][x];
      }
    }
  }

  for (int x = 0; x < C; x++) {
    if (lines[0][x] == BEAM) {
      ll cnt = 1 + dp[0][x];
      cout << cnt << endl;
    }
  }
}

int main() {
  // part1();
  part2();
  return 0;
}
