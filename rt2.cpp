// Problem: Round Trip II
// Judge: CSES
// URL: https://cses.fi/problemset/task/1678
// Memory Limit: 512 MB
// Time Limit: 1000 ms
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> visited, on_stack;
vector<int> cycle;

bool dfs(int node) {
	visited[node] = on_stack[node] = true;
	for (int next : graph[node]) {
		if (on_stack[next]) {
			cycle.push_back(node);  // start cycle
			on_stack[node] = on_stack[next] = false;
			return true;
		} else if (!visited[next]) {
			if (dfs(next)) {  // continue cycle
				if (on_stack[node]) {
					cycle.push_back(node);
					on_stack[node] = false;
					return true;
				} else {  // found u again
					cycle.push_back(node);
					return false;
				}
			}

			if (!cycle.empty()) {
				return false;  // finished with cycle
			}
		}
	}

	on_stack[node] = false;
	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	graph = vector<vector<int>>(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}

	visited = vector<bool>(n);
	on_stack = vector<bool>(n);
	for (int i = 0; cycle.empty() && i < n; i++) { dfs(i); }

	if (cycle.empty()) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		reverse(cycle.begin(), cycle.end());
		cout << cycle.size() + 1 << "\n";
		for (int node : cycle) { cout << node + 1 << " "; }
		cout << cycle[0] + 1 << endl;
	}
}
