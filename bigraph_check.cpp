#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using vi = vector<int>;
using vvi = vector<vector<int>>;


void dfs(vvi& graph, int v, vi& used, int num, bool& ans) {
    for (auto& u : graph[v]) {
        if (used[u] == 0) {
            used[u] = 3 - num;
            dfs(graph, u, used, 3 - num, ans);
        }
        if (used[u] == num) {
            ans = false;
        }
    }
}

// n - number of vertexes
bool bigraph_check(vvi& graph, int n) {
    vi used(n + 1, 0);
    bool ans = true;
    for (int i = 1; i < n + 1; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            dfs(graph, i, used, 1, ans);
        }
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    bool ans = bigraph_check(graph, n);

    if (ans) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }
}
