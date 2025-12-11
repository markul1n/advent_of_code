#include "../aoc.cpp"

unordered_map<string, vector<string>> getGraph(vector<string> lines) {
  unordered_map<string, vector<string>> graph;
  for (auto line : lines) {
    auto parts = split(line, ':');
    auto source = parts[0];
    trim(source);
    auto destionations = splitRegex(parts[1], "\\s+");
    for (auto d : destionations) {
      graph[source].push_back(d);
    }
  }
  return graph;
}

ll countPaths(string node, unordered_map<string, vector<string>> &graph,
              unordered_map<string, ll> &cache) {

  if (node == "out") {
    return 1;
  }

  if (cache.contains(node)) {
    return cache[node];
  }

  ll total = 0;

  for (string nxt : graph[node]) {
    total += countPaths(nxt, graph, cache);
  }

  cache[node] = total;
  return total;
}

ll countPathsWithDevices(string node, bool fft, bool dac,
                         unordered_map<string, vector<string>> &graph,
                         unordered_map<string, ll> &cache) {

  if (node == "out") {
    return (fft && dac) ? 1 : 0;
  }

  string key = node + (fft ? "t" : "f") + (dac ? "t" : "f");

  if (cache.contains(key)) {
    return cache[key];
  }

  ll total = 0;

  for (string nxt : graph[node]) {
    total += countPathsWithDevices(nxt, fft | node == "fft",
                                   dac | node == "dac", graph, cache);
  }
  cache[key] = total;
  return total;
}

void part1() {
  auto lines = readLines("input_1.txt");
  auto graph = getGraph(lines);
  unordered_map<string, ll> cache;

  ll res = countPaths("you", graph, cache);

  cout << res << endl;
}

void part2() {
  auto lines = readLines();
  auto graph = getGraph(lines);
  unordered_map<string, ll> cache;

  ll res = countPathsWithDevices("svr", false, false, graph, cache);

  cout << res << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
