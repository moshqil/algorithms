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


void colorful_dfs(vvi& rev_graph, int& v, vi& used, int num) {
    for (auto& u : rev_graph[v]) {
        if (used[u] == 0) {
            used[u] = num;
            colorful_dfs(rev_graph, u, used, num);
        }
    }
}

vi graph_condensation(vvi graph, vvi& rev_graph, int n, int m) {
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
    int num = 0;
    vi new_used(n + 1, 0);
    for (int i = n; i > 0; i--) {
        int v = topsort[i];
        if (new_used[v] == 0) {
            new_used[v] = ++num;
            colorful_dfs(rev_graph, v, new_used, num);
        }
    }
    return new_used;
}


int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    vvi rev_graph(n + 1);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        rev_graph[u].push_back(v);
    }
    
    vi ans = graph_condensation(graph, rev_graph, n, m);
    for (int i = 1; i < n + 1; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
