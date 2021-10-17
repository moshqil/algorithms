#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;


void path(int v, vi& from, vi& p, int& end) {
    p.push_back(v);
    if (v == end) {
        return;
    }
    if (from[v] != 0) {
        path(from[v], from, p, end);
    }
}


void dfs(vvi& graph, int v, vb& used, pair<int, int>& ans, vi& from) {
    for (auto& u : graph[v]) {
        if (!used[u]) {
            used[u] = true;
            from[u] = v;
            dfs(graph, u, used, ans, from);
        } else if (u != from[v]) {
            ans = {u, v};
        }
    }
}

// returns vector with cicle (empty in case there is no cicle)
vi cicle_search(vvi& graph, int n) {
    vb used(n + 1, false);
    vi from(n + 1, 0);
    pair<int, int> ans = {0, 0};
    for (int i = 1; i < n + 1; i++) {
        if (!used[i]) {
            used[i] = true;
            dfs(graph, i, used, ans, from);
        }
        if (ans.first != 0) {
            break;
        }
    }
    if (ans.first == 0) {
        return {};
    }
    vi p;
    path(ans.first, from, p, ans.second);
    return p;
}

int main() {
    int n;
    cin >> n;
    vvi matrix(n);
    for (auto& elem : matrix) {
        elem.resize(n);
    }
    vvi graph(n + 1);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 1) {
                graph[i + 1].push_back(j + 1);
            }
        }
    }
    
    vi cicle = cicle_search(graph, n);
}
