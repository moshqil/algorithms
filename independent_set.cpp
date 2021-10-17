#include <iostream>
#include <vector>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvb = vector<vector<bool>>;

bool recursive_check(vvb& graph, int v, int n, int k, vi& current) {
    if (v == n) {
        return current.size() >= k;
    }
    if (k - current.size() > n - v) {
        return false;
    }
    bool related_to_current = false;
    for (auto& elem : current) {
        if (graph[elem][v]) {
            related_to_current = true;
            break;
        }
    }
    bool try_without = recursive_check(graph, v + 1, n, k, current);
    if (try_without) {
        return true;
    }
    bool try_with = false;
    if (!related_to_current) {
        current.push_back(v);
        if (current.size() == k) {
            return true;
        }
        try_with = recursive_check(graph, v + 1, n, k, current);
        current.pop_back();
    }
    return try_with;
}

int main() {
    int v, s; cin >> v >> s;
    int q; cin >> q;
    vvb graph(v);
    for (auto& elem : graph) {
        elem.resize(v, false);
    }
    for (int i = 0; i < q; i++) {
        int b, e; cin >> b >> e;
        e--; b--;
        graph[e][b] = true; graph[b][e] = true;
    }
    vi current;
    if (recursive_check(graph, 0, v, s, current)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
