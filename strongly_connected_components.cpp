#include <iostream>
#include <vector>
#include <set>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vs = vector<set<int>>;


void dfs(vvi& graph, int v, int c, vb& used, vs& comp) {
    for (auto& u : graph[v]) {
        if (!used[u]) {
            used[u] = true;
            comp[c].insert(u);
            dfs(graph, u, c, used, comp);
        }
    }
}

// n - vertexes, m - edges
// returns vector of sets, ith set - ith component
vs strongly_connected_components(vvi& graph, int n, int m) {
    vb used(n + 1, false);
    int c = 0;
    vs comp(1);
    for (int i = 1; i < n + 1; i++) {
        if (!used[i]) {
            used[i] = true;
            comp.push_back({i});
            dfs(graph, i, ++c, used, comp);
        }
    }
    return comp;
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

    auto comp = strongly_connected_components(graph, n, m);

    // unnecessary part to display the results
    cout << comp.size() - 1 << '\n';
    for (auto& s : comp) {
        if (s.empty()) {
            continue;
        }
        cout << s.size() << '\n';
        for (auto& elem : s) {
            cout << elem << ' ';
        }
        cout << '\n';
    }
}
