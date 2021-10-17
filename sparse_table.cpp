// Static RMQ

#include <iostream>
#include <vector>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int INF = -1;
vi LOG2(100003, -1);


int f_pow(int i) {
    return 1 << i;
}

int max_log(int l) {
    if (l == 0) {return 0;}
    if (l == 1) {return 0;}
    if (LOG2[l] == -1) {
        LOG2[l] = max_log(l / 2) + 1;
    }
    return LOG2[l];
}

vvi sparse_table_creation(vi& a) {
    int l = max_log(a.size()) + 1;
    vvi st(a.size());
    for (int i = 0; i < a.size(); i++) {
        st[i].assign(l, INF);
    }
    for (int i = 0; i < a.size(); i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; j < l; j++) {
        for (int i = 0; i < a.size() - f_pow(j); i++) {
            st[i][j] = max(st[i][j - 1], st[i + f_pow(j - 1)][j - 1]);
        }
    }
    return st;
}

int main() {
    int n; cin >> n;
    vi a(n + 1);
    for (int i = 0; i < n; i++) {cin >> a[i];}
    a[n] = INF;
    a.push_back(INF);
    vvi sp = sparse_table_creation(a);
    long long ans = 0;
    int k; cin >> k;
    long long x0, x1;
    cin >> x0;
    x1 = (11173 * x0 + 1) % 1000000007; // weird way to generate queries
    for (int i = 0; i < k; i++) {
        int l = min(x0 % n, x1 % n);
        int r = max(x0 % n, x1 % n); r++;
        int len = max_log(r - l);
        ans = (ans + max(sp[l][len], sp[r - (1 << len)][len])) % 1000000007;
        // cout << l << ' ' << r << endl;
        // cout << max(sp[l][len], sp[r - (1 << len)][len]) << endl;
        x0 = (11173 * x1 + 1) % 1000000007;
        x1 = (11173 * x0 + 1) % 1000000007;
    }
    cout << ans << endl;
}
