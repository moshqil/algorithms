#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;


void dfs(vvi& graph, int v, vi& used, vi& topsort, bool& cicle, vvi& new_graph, int parent) {
    for (auto& u : graph[v]) {
        if (used[u] == 0) {
            used[u] = 1;
            new_graph[u].push_back(v);
            // cout << u << ' ' << v << endl;
            dfs(graph, u, used, topsort, cicle, new_graph, v);
        } else if (u != parent) {
            new_graph[u].push_back(v);
            // cout << u << ' ' << v << '!' << endl;
        }
    }
    used[v] = 2;
    topsort.push_back(v);
}


void colorful_dfs(vvi& new_graph, vi& used, int num, int v) {
    for (auto& u : new_graph[v]) {
        if (used[u] == 0) {
            used[u] = num;
            colorful_dfs(new_graph, used, num, u);
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    vi ed_from(m + 1);
    vi ed_to(m + 1);
    unordered_map<int, int> ed;
    for (int i = 1; i < m + 1; i++) {
        int v, u;
        cin >> v >> u;
        ed_from[i] = v;
        ed_to[i] = u;
        if (v == u) {
            continue;
        }
        ed[v * 20001 + u] += 1;
        ed[u * 20001 + v] += 1;
        if (ed[v * 20001 + u] > 1) {
            continue;
        }
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    vvi new_graph(n + 1);
    vi used(n + 1, 0);
    vi topsort(1, 0);
    bool cicle = false;
    for (int i = 1; i < n + 1; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            dfs(graph, i, used, topsort, cicle, new_graph, 0);
        }
    }
    vi new_used(n + 1, 0);
    int num = 0;
    for (int i = n; i > 0; i--) {
        if (new_used[topsort[i]] == 0) {
            new_used[topsort[i]] = ++num;
            colorful_dfs(new_graph, new_used, num, topsort[i]);
        }
    }
    vi ans;
    for (int i = 1; i < ed_from.size(); i++) {
        if (new_used[ed_from[i]] != new_used[ed_to[i]]) {
            if (ed[ed_from[i] * 20001 + ed_to[i]] > 1) {
                continue;
            }
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (auto& elem : ans) {
        cout << elem << ' ';
    }
    cout << endl;
}
