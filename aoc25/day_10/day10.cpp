#include "../aoc.cpp"
#include <regex>
#include <z3++.h>

vector<string> split_brackets(const string &text) {
  vector<string> out;
  regex bracket_pattern(R"([\(\)\[\]\{\}<>])");

  sregex_token_iterator iter(text.begin(), text.end(), bracket_pattern, -1);
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

int getMin(int i, int curr, vector<int> &buttons,
           unordered_map<ll, int> &memo) {

  if (!curr) {
    return 0;
  }

  if (i == (int)buttons.size()) {
    return 999;
  }

  ll key = ((ll)curr << 30) | i;

  if (memo.contains(key)) {
    return memo[key];
  }

  int res = min(1 + getMin(i + 1, curr ^ buttons[i], buttons, memo),
                getMin(i + 1, curr, buttons, memo));

  memo[key] = res;

  return res;
}
void part1() {
  auto lines = readLines();
  int res = 0;
  for (auto line : lines) {
    auto parts = split_brackets(line);
    int L = parts.size();
    auto config = parts[0];
    vector<int> buttons;
    for (int i = 1; i < L - 1; i++) {
      auto btn = parseInts(parts[i]);
      int mask = 0;
      for (int num : btn) {
        mask |= (1 << num);
      }
      buttons.push_back(mask);
    }

    int target = 0;
    int cfg_len = config.size();
    for (int i = 0; i < cfg_len; i++) {
      if (config[i] == '#') {
        target |= (1 << i);
      }
    }

    unordered_map<ll, int> memo;
    res += getMin(0, target, buttons, memo);
  }

  cout << res << endl;
}

void part2() {

  auto solve = [](const auto &A, const auto &C) {
    z3::context ctx;
    z3::optimize opt(ctx);

    std::vector<z3::expr> x;
    for (size_t i = 0; i < A[0].size(); i++) {
      x.push_back(ctx.int_const(("x" + std::to_string(i)).c_str()));
      opt.add(x[i] >= 0);
    }

    for (size_t i = 0; i < A.size(); i++) {
      z3::expr eq = ctx.int_val(0);
      for (size_t j = 0; j < A[i].size(); j++) {
        eq = eq + ctx.int_val((int)A[i][j]) * x[j];
      }
      opt.add(eq == ctx.int_val((int)C[i]));
    }

    z3::expr sum = ctx.int_val(0);
    for (auto &var : x)
      sum = sum + var;
    opt.minimize(sum);

    int result = 0;
    if (opt.check() == z3::sat) {
      auto model = opt.get_model();
      for (auto &var : x) {
        result += model.eval(var).get_numeral_int();
      }
    }
    return result;
  };

  auto lines = readLines();
  int res = 0;
  for (auto line : lines) {
    auto parts = split_brackets(line);
    int L = parts.size();
    auto joltages = parseInts(parts[L - 1]);
    vector<vector<int>> buttons;
    for (int i = 1; i < L - 1; i++) {
      auto btn = parseInts(parts[i]);
      buttons.push_back(btn);
    }
    int B = buttons.size();
    int J = joltages.size();

    vector<vector<int>> A(J, vector<int>(B));

    // A * X = joltages
    // find min(X)

    for (int i = 0; i < B; i++) {
      auto button = buttons[i];
      for (int j : button) {
        A[j][i] = 1;
      }
    }

    res += solve(A, joltages);
  }

  cout << res << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
