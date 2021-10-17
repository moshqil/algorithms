#include <iostream>
#include<vector>
#include <array>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vva = vector<vector<array<int, 2>>>;
using vb = vector<bool>;
using ll = long long;
const int INF = 1000001;

vi LOG2(INF, -1);

int max_log(int l) {
    if (l == 0) {
        return 0;
    }
    if (l == 1) {
        return 0;
    }
    if (LOG2[l] == -1) {
        LOG2[l] = max_log(l / 2) + 1;
    }
    return LOG2[l];
}

vvi graph_creation(int n) {
    vvi graph(n);
    for (int i = 0; i < n - 1; i++) {
        int j;
        cin >> j;
        graph[j].push_back(i + 1);
    }
    return graph;
}

void dfs(vvi& graph, vi& depth, vi& first, vi& last, vi& a, int v, int k) {
    depth[v] = k;
    a.push_back(v);
    first[v] = a.size() - 1;
    for (int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        dfs(graph, depth, first, last, a, u, k + 1);
        a.push_back(v);
    }
    last[v] = a.size() - 1;
}

int f_pow(int i) {
    return 1 << i;
}

vva sparse_table_creation(vi& a, vi& depth) {
    int l = max_log(a.size()) + 1;
    vva st(a.size());
    for (int i = 0; i < a.size(); i++) {
        st[i].assign(l, {INF, INF});
    }
    for (int i = 0; i < a.size(); i++) {
        st[i][0] = {depth[a[i]], a[i]};
    }
    for (int j = 1; j < l; j++) {
        for (int i = 0; i < a.size() - f_pow(j); i++) {
            if (st[i][j - 1][0] < st[i + f_pow(j - 1)][j - 1][0]) {
                st[i][j] = {st[i][j - 1][0], st[i][j - 1][1]};
            } else {
                st[i][j] = {st[i + f_pow(j - 1)][j - 1][0], st[i + f_pow(j - 1)][j - 1][1]};
            }
        }
    }
    return st;
}

int lca(int v1, int v2, vi& first, vi& last, vva& sp) {
    int r = max(last[v2], last[v1]) + 1;
    int l = min(first[v2], first[v1]);
    int len = max_log(r - l);
    array<int, 2> ans1 = sp[l][len];
//    cout << len << "!" << (r - l) << " " << sp.size() << " " << (r - (1 << len)) << endl;
    array<int, 2> ans2 = sp[r - (1 << len)][len];
    if (ans1[0] < ans2[0]) {
        return ans1[1];
    }
    return ans2[1];
}

int main() {
    int n, m;
    ll x, y, z, a1, a2;
    cin >> n >> m;
    vvi graph = graph_creation(n);
    cin >> a1 >> a2;
    cin >> x >> y >> z;
    vi depth(n), first(n), last(n), a;
    dfs(graph, depth, first, last, a, 0, 0);
    vva sp = sparse_table_creation(a, depth);
    ll ans = 0;
    int v = 0;
    for (int i = 0; i < m; i++) {
        int v1 = (int)((a1 + ((ll)v)) % ((ll)n));
        int v2 = (int)a2;
        v = lca(v1, v2, first, last, sp);
        ans += (ll)v;
        a1 = ((x * a1 + y * a2 + z) % ((ll)n)); // weird way of generating querries
        a2 = ((x * a2 + y * a1 + z) % ((ll)n));
    }
    cout << ans << endl;
}
