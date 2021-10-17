#include <iostream>
#include <vector>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

bool dfs(int v, vvi& graph_a_b, vb& used, vi& match) {
	if (used[v]) return false;
	used[v] = true;
	for (auto& pair : graph_a_b[v]) {
		if (match[pair] == -1) {
			match[pair] = v;
			return true;
		}
	}
	for (auto& pair : graph_a_b[v]) {
		if (dfs(match[pair], graph_a_b, used, match)) {
			match[pair] = v;
			return true;
		}
	}
	return false;
}


int main() {
	int n, m;
	cin >> n >> m;
	vvi graph(n);
	for (int i = 0; i < n; i++) {
		int to; cin >> to;
		while (to != 0) {
			graph[i].push_back(--to);
			cin >> to;
		}
	}
	vi match(m, -1);
	vb used(n, false);
	int c = 0;
	for (int v = 0; v < n; v++) {
		fill(used.begin(), used.end(), false);
		if (dfs(v, graph, used, match)) c++;

	}
	cout << c << endl;
	for (int v = 0; v < m; v++) {
		if (match[v] == -1) continue;
		cout << match[v] + 1 << ' ' << v + 1 << endl;
	}
}
