#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;


void dfs(vvi& graph, int v, vb& used, int t, vi& tin, vi& up, vb& ans, int parent) {
    int num_kids = 0;
    for (auto& u : graph[v]) {
        if (!used[u]) {
            num_kids++;
            used[u] = true;
            tin[u] = ++t;
            up[u] = tin[u];
            dfs(graph, u, used, t, tin, up, ans, v);
            up[v] = min(up[v], up[u]);
            if (up[u] >= tin[v] && parent != 0) {
                ans[v] = true;
            }
        } else {
            up[v] = min(tin[u], up[v]);
        }
    }
    if (parent == 0 && num_kids > 1) {
        ans[v] = true;
    }
}

// returns a bool vector; a[i] if ith vertex is an articulation point
// i numeration is from 1
vb art_points_search(vvi graph, int n, int m) {
    vi tin(n + 1, 0);
    vi up(n + 1, 0);
    vb used(n + 1, 0);
    vb ans(n + 1, false);
    int t = 0;
    for (int i = 1; i < n + 1; i++) {
        if (!used[i]) {
            used[i] = true;
            tin[i] = ++t;
            up[i] = tin[i];
            dfs(graph, i, used, t, tin, up, ans, 0);
        }
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    
    vb ans = art_points_search(graph, n, m);
    
    // unnecessary couts for displaying results
    vi ans_real;
    for (int i = 1; i < n + 1; i++) {
        if (ans[i]) {
            ans_real.push_back(i);
        }
    }
    cout << ans_real.size() << endl;
    for (auto& elem : ans_real) {
        cout << elem << endl;
    }
    cout << endl;
}
