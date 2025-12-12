#include "../aoc.cpp"

ll geometric_sum(ll a, ll r, ll n) {
  if (r == 1) {
    return n;
  }
  ll res = a * (1 - powl(r, n + 1)) / (1 - r);
  if (res < 0) {
    // Overflow
    return 1e18;
  }
  return res;
}

void part1() {

  string line = readLine();

  auto parts = split(line, ',');
  vector<pll> ranges;

  for (auto p : parts) {
    auto range = parseLongs(line);
    ranges.push_back({range.at(0), range.at(1)});
  }

  ll total = 0;

  for (auto [l, r] : ranges) {
    int L = log10(l) + 1;
    ll left = pow(10, L / 2 - 1);
    while (left <= r) {
      int H = log10(left) + 1;
      ll num = left + left * pow(10, H);
      if (num > r) {
        break;
      }
      if (num >= l) {
        total += num;
      }
      left++;
    }
  }

  cout << "total: " << total << endl;
}

void part2() {

  string line = readLine();

  auto parts = split(line, ',');
  vector<pll> ranges;

  for (auto p : parts) {
    auto range = parseLongs(p);
    ranges.push_back({range.at(0), range.at(1)});
  }

  ll total = 0;

  set<ll> seen;

  for (auto [l, r] : ranges) {

    for (int i = 1; i < 18; i++) {
      // int L = log10(l) + 1;
      ll left = 1;
      while (left <= r) {
        int L = log10(left) + 1;
        ll p = (ll)powl(10, L);
        //  left + left * p + left*(p^2) + left * (p^3)
        ll curr = geometric_sum(left, p, i);

        if (curr > r || curr < 0) {
          break;
        }

        if (curr >= l && !seen.contains(curr)) {
          seen.insert(curr);
          total += curr;
        }
        left++;
      }
    }
  }

  cout << "total: " << total << endl;
}

int main() {
  part1();
  part2();
  return 0;
}