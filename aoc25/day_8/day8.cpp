#include "../aoc.cpp"

using namespace std;

class DisjointSet {
public:
  vector<int> parent;

  DisjointSet(int n) {
    parent = vector<int>(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent.at(x) == x) {
      return x;
    }
    return parent.at(x) = find(parent.at(x));
  }

  bool connect(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      parent.at(b) = a;
      return true;
    }

    return false;
  }
};

void part1() {
  const int CONNECTIONS = 1000;
  auto lines = readLines();

  int N = lines.size();

  vector<tuple<ll, int, int>> distances;
  for (int i = 0; i < N; i++) {

    auto line = lines[i];
    auto co = split(line, ',');

    ll x = stol(co[0]);
    ll y = stol(co[1]);
    ll z = stol(co[2]);

    for (int j = i + 1; j < N; j++) {

      auto line = lines[j];
      auto co = split(line, ',');

      ll x2 = stol(co[0]);
      ll y2 = stol(co[1]);
      ll z2 = stol(co[2]);

      ll xd = x2 - x;
      ll yd = y2 - y;
      ll zd = z2 - z;

      ll d = xd * xd + yd * yd + zd * zd;

      distances.push_back({d, i, j});
    }
  }

  sort(distances.begin(), distances.end(),
       [](auto a, auto b) { return get<0>(a) > get<0>(b); });

  DisjointSet ds(N);

  for (int k = 0; k < CONNECTIONS; k++) {
    auto [_, i, j] = distances.back();
    ds.connect(i, j);
    distances.pop_back();
  }

  vector<ll> sizes(N);
  for (int i = 0; i < N; i++) {
    sizes[ds.find(i)]++;
  }
  sort(sizes.begin(), sizes.end(), greater<int>());

  ll res = sizes[0] * sizes[1] * sizes[2];

  cout << res << endl;
}

void part2() {
  auto lines = readLines();

  int N = lines.size();

  vector<tuple<ll, int, int>> distances;
  for (int i = 0; i < N; i++) {

    auto line = lines[i];
    auto co = split(line, ',');

    ll x = stol(co[0]);
    ll y = stol(co[1]);
    ll z = stol(co[2]);

    for (int j = i + 1; j < N; j++) {

      auto line = lines[j];
      auto co = split(line, ',');

      ll x2 = stol(co[0]);
      ll y2 = stol(co[1]);
      ll z2 = stol(co[2]);

      ll xd = x2 - x;
      ll yd = y2 - y;
      ll zd = z2 - z;

      ll d = xd * xd + yd * yd + zd * zd;

      distances.push_back({d, i, j});
    }
  }

  sort(distances.begin(), distances.end(),
       [](auto a, auto b) { return get<0>(a) > get<0>(b); });

  DisjointSet ds(N);

  int groups = N;

  while (true) {
    auto [_, i, j] = distances.back();
    if (ds.connect(i, j)) {

      groups--;
      if (groups == 1) {
        ll x1 = stol(split(lines[i], ',')[0]);
        ll x2 = stol(split(lines[j], ',')[0]);

        cout << x1 * x2 << endl;
      }
    }
    distances.pop_back();
  }
}
int main() {
  // part1();
  part2();
  return 0;
}
