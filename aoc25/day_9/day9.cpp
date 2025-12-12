#include "../aoc.cpp"

vector<pair<int, int>> getCoords() {
  auto lines = readLines();
  vector<pair<int, int>> coords;
  for (auto line : lines) {
    auto xy = parseInts(line);
    int x = xy.at(0);
    int y = xy.at(1);
    coords.push_back({x, y});
  }
  return coords;
}

void part1() {
  auto coords = getCoords();
  int N = coords.size();
  ll best = 0;

  for (int i = 0; i < N; i++) {
    auto [x1, y1] = coords[i];
    for (int j = i + 1; j < N; j++) {
      auto [x2, y2] = coords[j];
      ll w = abs(x2 - x1) + 1;
      ll h = abs(y2 - y1) + 1;
      best = max(best, w * h);
    }
  }

  cout << best << endl;
}

int getCompressed(vector<int> &values, int target) {
  return lower_bound(values.begin(), values.end(), target) - values.begin();
}

void part2() {
  const char BORDER = 'B';
  const char OUTSIDE = 'O';
  const char NOT_VISITED = '.';

  auto coords = getCoords();
  int N = coords.size();

  set<int> xes_set;
  set<int> ys_set;

  for (int i = 0; i < N; i++) {
    auto [x, y] = coords[i];
    xes_set.insert(x);
    ys_set.insert(y);
  }

  vector<int> xes(xes_set.begin(), xes_set.end());
  vector<int> ys(ys_set.begin(), ys_set.end());

  int R = ys.size();
  int C = xes.size();

  vector<vector<char>> grid(R, vector<char>(C, NOT_VISITED));

  for (int i = 0; i < N; i++) {
    auto [x1, y1] = coords[i];
    auto [x2, y2] = coords[(i + 1) % N];

    int l = getCompressed(xes, min(x1, x2));
    int r = getCompressed(xes, max(x1, x2));
    int t = getCompressed(ys, min(y1, y2));
    int b = getCompressed(ys, max(y1, y2));

    for (int x = l; x <= r; x++) {
      for (int y = t; y <= b; y++) {
        grid[y][x] = BORDER;
      }
    }
  }

  queue<pair<int, int>> q;

  for (int x = 0; x < C; x++) {
    if (grid[0][x] == NOT_VISITED) {
      grid[0][x] = OUTSIDE;
      q.push({0, x});
    }
    if (grid[R - 1][x] == NOT_VISITED) {
      grid[R - 1][x] = OUTSIDE;
      q.push({R - 1, x});
    }
  }

  for (int y = 0; y < R; y++) {
    if (grid[y][0] == NOT_VISITED) {
      grid[y][0] = OUTSIDE;
      q.push({y, 0});
    }
    if (grid[y][C - 1] == NOT_VISITED) {
      grid[y][C - 1] = OUTSIDE;
      q.push({y, C - 1});
    }
  }

  vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  while (!q.empty()) {
    auto [y, x] = q.front();
    q.pop();

    for (auto [dy, dx] : dirs) {
      int ny = y + dy;
      int nx = x + dx;
      if (ny >= 0 && ny < R && nx >= 0 && nx < C &&
          grid[ny][nx] == NOT_VISITED) {
        grid[ny][nx] = OUTSIDE;
        q.push({ny, nx});
      }
    }
  }

  ll best = 0;

  for (int i = 0; i < N; i++) {
    auto [x1, y1] = coords[i];

    for (int j = i + 1; j < N; j++) {
      auto [x2, y2] = coords[j];

      int l = getCompressed(xes, min(x1, x2));
      int r = getCompressed(xes, max(x1, x2));
      int t = getCompressed(ys, min(y1, y2));
      int b = getCompressed(ys, max(y1, y2));

      bool good = true;

      for (int x = l; x <= r; x++) {
        for (int y = t; y <= b; y++) {
          if (grid[y][x] == OUTSIDE) {
            good = false;
            break;
          }
        }
        if (!good)
          break;
      }

      if (good) {
        ll w = abs(x2 - x1) + 1;
        ll h = abs(y2 - y1) + 1;
        best = max(best, w * h);
      }
    }
  }

  cout << best << endl;
}

int main() {
  // part1();
  part2();
  return 0;
}
