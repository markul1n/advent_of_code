#include "../aoc.cpp"

void part1() {
  vector<string> lines = readLines();

  ll res = 0;
  for (string l : lines) {
    int N = l.size();
    int best = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        int a = l[i] - '0';
        int b = l[j] - '0';
        best = max(best, a * 10 + b);
      }
    }
    res += best;
  }

  cout << "res : " << res << endl;
}

ll go(int i, int taken, vector<vector<ll>> &memo, vector<int> &nums) {

  int N = nums.size();

  if (taken == 12) {
    return 0;
  }
  if (i == N) {
    return -1e17;
  }

  if (memo[i][taken] != -1) {
    return memo[i][taken];
  }

  ll best =
      max(go(i + 1, taken, memo, nums), (ll)(nums[i] * pow(10, 11 - taken) +
                                             go(i + 1, taken + 1, memo, nums)));

  memo[i][taken] = best;

  return best;
}

void part2() {

  vector<string> lines = readLines();

  ll res = 0;
  for (string l : lines) {
    int N = l.size();
    vector<int> nums;
    for (int i = 0; i < N; i++) {
      int num = l[i] - '0';
      nums.push_back(num);
    }
    vector<vector<ll>> memo(N + 1, vector<ll>(12, -1));
    ll best = go(0, 0, memo, nums);
    res += best;
  }

  cout << "res : " << res << endl;
}

int main() {
  // part1();
  part2();
  return 0;
}
