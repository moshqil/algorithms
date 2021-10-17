#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;


int bfs(vvi& graph, vi& dist, vb& used, int s, int f) {
    queue<int> q;
    q.push(s);
    used[s] = true;
    dist[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& u : graph[v]) {
            if (!used[u]) {
                used[u] = true;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist[f];
}


int main() {
    int n;
    cin >> n;
    vvi graph(n + 1);
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int c;
            cin >> c;
            if (c == 1) {
                graph[i].push_back(j);
            }
        }
    }
    int s, f;
    cin >> s >> f;
    vb used(n + 1, false);
    vi dist(n + 1, -1);
    cout << bfs(graph, dist, used, s, f) << endl;
}
