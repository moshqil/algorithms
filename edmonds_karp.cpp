#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;


struct edge {
	int from, to;
	int weight;
	edge * rev;
	bool im;
};

int find_min(vector<edge*>& from) {
	int cur_min = numeric_limits<int>::max();
	edge * now = from[from.size() - 1];
	while (now != nullptr) {
		cur_min = min(cur_min, now->weight);
		now = from[now->from];
	}
	return cur_min;
}

void change_path(vector<edge*>& from, int path_min) {
	edge * now = from[from.size() - 1];
	while (now != nullptr) {
		now->weight -= path_min;
		now->rev->weight += path_min;
		now = from[now->from];
	}
}

bool bfs(vector<vector<edge*>>& graph, int& ans) {
	queue<edge*> q;
	vector<edge*> from(graph.size(), nullptr); 
	for (auto& e : graph[0]) {
		q.push(e);
	}
	while (!q.empty()) {
		auto e = q.front();
		q.pop();
		if (e->weight == 0 || e->to == 0) continue;
		if (from[e->to] == nullptr) {
			from[e->to] = e;
			for (auto& elem : graph[e->to]) {
				q.push(elem);
			}
		}
	}
	if (from[from.size() - 1] == nullptr) {
		return false;
	}
	int path_min = find_min(from);
	change_path(from, path_min);
	ans += path_min;
	return true;
} 

int main() {
	int n, m; cin >> n >> m;
	vector<vector<edge*>> graph(n);
	for (int i = 0; i < m; i++) {
		int f, t, w; cin >> f >> t >> w;
		f--; t--;
		edge * new_edge = new edge {f, t, w, nullptr, false};
		edge * new_rev_edge = new edge {t, f, 0, new_edge, true};
		new_edge->rev = new_rev_edge;
		graph[f].push_back(new_edge);
		graph[t].push_back(new_rev_edge);
	}
	int ans = 0;
	while (bfs(graph, ans)) {}
	cout << ans << endl;
}
