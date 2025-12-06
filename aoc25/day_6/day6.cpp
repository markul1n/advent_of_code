#include "../aoc.cpp"

using namespace std;

void part1() {

  auto plus = [](ll a, ll b) { return a + b; };
  auto multiply = [](ll a, ll b) { return a * b; };

  auto grid = readGrid();
  int R = grid.size();
  int C = grid[0].size();

  ll total = 0;
  for (int x = 0; x < C; x++) {

    ll curr = stol(grid[0][x]);
    auto op = grid[R - 1][x] == "+" ? plus : multiply;

    for (int i = 1; i < R - 1; i++) {
      ll num = stol(grid[i][x]);

      curr = op(curr, num);
    }
    total += curr;
  }

  cout << "total : " << total << endl;
}

void part2() {
  auto plus = [](ll a, ll b) { return a + b; };
  auto multiply = [](ll a, ll b) { return a * b; };

  auto lines = readLines();
  int R = lines.size();
  int C = lines.at(0).size();

  ll total = 0;
  function<ll(ll, ll)> op = plus;
  ll curr = -1;
  for (int x = 0; x < C; x++) {

    if (lines[R - 1][x] != ' ') {
      op = lines[R - 1][x] == '+' ? plus : multiply;
    }

    ll num = 0;
    bool emptyColumn = true;
    for (int y = 0; y < R - 1; y++) {
      if (lines[y][x] != ' ') {
        emptyColumn = false;
        int digit = lines[y][x] - '0';
        num = num * 10 + digit;
      }
    }

    if (!emptyColumn) {
      if (curr == -1) {
        curr = num;
      } else {
        curr = op(curr, num);
      }
    } else {
      total += curr;
      curr = -1;
    }
  }

  total += curr;

  cout << "total : " << total << endl;
}

int main() {
  // part1();
  part2();
  return 0;
}
