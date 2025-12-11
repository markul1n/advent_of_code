#include "../aoc.cpp"

void part1() {
  vector<string> lines = readLines();

  int L = 100;

  int curr = 50;

  int pass = 0;

  for (string op : lines) {
    int distance = stoi(op.substr(1));

    if (op[0] == 'R') {
      curr += distance;
    } else {
      curr -= distance;
    }
    curr = (curr % L + L) % L;

    if (curr == 0) {
      pass++;
    }
  }

  cout << "password: " << pass << endl;
}

void part2() {

  vector<string> lines = readLines();

  int L = 100;

  int curr = 50;

  int pass = 0;

  for (string op : lines) {
    int distance = stoi(op.substr(1));

    if (op[0] == 'R') {
      curr += distance;
      pass += curr / L;
    } else {
      int normalized = (L - curr) % L + distance;
      pass += (normalized / L);
      curr -= distance;
    }

    curr = (curr % L + L) % L;
  }

  cout << "password: " << pass << endl;
}

int main() {
  part2();
  return 0;
}