#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<long long>;
using vvl = vector<vl>;
int INF = 20000000;


void fb(int n) {
    vl dist(n + 1, INF);
    dist[1] = 0;
    for (int i = 1; i < n + 1; i++) {
        bool opt = true;
        for (int u = 1; u < n + 1; u++) {
            for (int v = u + 1; v < n + 1; v++) {
                int len = (179 * u + 719 * v) % 1000 - 500; // specific edge length calculation
                if (dist[v] > dist[u] + len) {
                    dist[v] = min(dist[v], dist[u] + len);
                    opt = false;
                }
            }
        }
        if (opt) {
            break;
        }
    }
    cout << dist[n] << endl;
}


int main() {
    int n;
    cin >> n;
    fb(n);
}
