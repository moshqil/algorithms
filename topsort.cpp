#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;


void dfs(vvi& graph, int v, vi& used, vi& tout, vi& topsort, bool& cicle) {
    for (auto& u : graph[v]) {
        if (used[u] == 0) {
            used[u] = 1;
            // tin[u] = ++t;
            dfs(graph, u, used, tout, topsort, cicle);
        } else if (used[u] == 1) {
            cicle = true;
        }
    }
    used[v] = 2;
    topsort.push_back(v);
}

vi topsort(vvi& graph, int n) {
    vi tin(n + 1, 0);
    vi tout(n + 1, 0);
    vi used(n + 1, 0);
    vi topsort(1, 0);
    int t = 0;
    bool cicle = false;
    for (int i = 1; i < n + 1; i++) {
        if (!used[i]) {
            used[i] = 1;
            // tin[i] = ++t;
            dfs(graph, i, used, tout, topsort, cicle);
        }
    }
    if (cicle) {
        return {};
    }
    return topsort;
}


int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
    }
    
    vi topsorted = topsort(graph, n);
}
