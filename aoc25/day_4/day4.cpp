#include "../aoc.cpp"
#include <bits/stdc++.h>

using namespace std;

char PAPER = '@';
char EMPTY = '.';


void part1() {
  vector<string> grid = readLines();
  int R = grid.size();
  int C = grid.at(0).size();
  int count = 0;
  for (int y = 0; y < R; y++) {
    for (int x = 0; x < C; x++) {
      int adj = 0;
      if (grid[y][x] != PAPER)
        continue;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          if (!dx && !dy)
            continue;
          int nx = x + dx;
          int ny = y + dy;
          if (nx >= 0 && nx < C && ny >= 0 && ny < R && grid[ny][nx] == PAPER) {
            adj++;
          }
        }
      }
      if (adj < 4) {
        count++;
      }
    }
  }

  cout << count << endl;
}

void part2() {

  vector<string> grid = readLines();
  int R = grid.size();
  int C = grid.at(0).size();
  int total = 0;
  while (true) {
    int count = 0;
    for (int y = 0; y < R; y++) {
      for (int x = 0; x < C; x++) {
        int adj = 0;
        if (grid[y][x] != PAPER)
          continue;
        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (!dx && !dy)
              continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < C && ny >= 0 && ny < R &&
                grid[ny][nx] == PAPER) {
              adj++;
            }
          }
        }
        if (adj < 4) {
          count++;
          grid[y][x] = EMPTY;
        }
      }
    }

    if (count == 0) {
      break;
    }
    total += count;
  }

  cout << total << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
