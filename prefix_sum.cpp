// Static RSQ problem

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vl = vector<long long>;
using vi = vector<int>;

int main() {
    int n; cin >> n;
    vl sum_pref(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
        long long c; cin >> c;
        sum_pref[i] = c + sum_pref[i - 1];
    }
    long long ans = 0;
    int k; cin >> k;
    long long x0, x1;
    cin >> x0;
    x1 = (11173 * x0 + 1) % 1000000007;
    for (int i = 0; i < k; i++) {
        int l = min(x0 % n, x1 % n);
        int r = max(x0 % n, x1 % n);
        ans = (ans + sum_pref[r + 1] - sum_pref[l]) % 1000000007;
        x0 = (11173 * x1 + 1) % 1000000007;
        x1 = (11173 * x0 + 1) % 1000000007;
    }
    cout << ans << endl;
}
