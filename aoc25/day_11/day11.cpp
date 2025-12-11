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

int dfs(string node, unordered_map<string, vector<string>> &graph) {

  if (node == "out") {
    return 1;
  }

  int total = 0;

  for (string nxt : graph[node]) {
    total += dfs(nxt, graph);
  }

  return total;
}

ll dfs2(string node, bool fft, bool dac,
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

  if (node == "fft") {
    fft = true;
  }

  if (node == "dac") {
    dac = true;
  }

  for (string nxt : graph[node]) {
    total += dfs2(nxt, fft, dac, graph, cache);
  }
  cache[key] = total;
  return total;
}

void part1() {
  auto lines = readLines("input_1.txt");
  unordered_map<string, vector<string>> graph = getGraph(lines);

  int res = dfs("you", graph);

  cout << res << endl;
}

void part2() {
  auto lines = readLines();
  unordered_map<string, vector<string>> graph = getGraph(lines);
  unordered_map<string, ll> cache;

  ll res = dfs2("svr", false, false, graph, cache);

  cout << res << endl;
}

int main() {
  part1();
  part2();
  return 0;
}
