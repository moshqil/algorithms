#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;


void dfs(vvi& graph, int v, vb& used, int& num) {
    for (auto& u : graph[v]) {
        if (!used[u]) {
            used[u] = true;
            dfs(graph, u, used, ++num);
        }
    }
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
    vb used(n + 1, false);
    used[1] = true;
    int num = 1;
    dfs(graph, 1, used, num);
    cout << num << '\n';
    for (size_t i = 0; i < used.size(); i++) {
        if (used[i]) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}
