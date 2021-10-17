#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int INF = 100000;


void floyd(vvi& dist, int n) {
    for (int i = 1; i < n + 1; i++) {
        for (int v = 1; v < n + 1; v++) {
            for (int u = 1; u < n + 1; u++) {
                dist[v][u] = min(dist[v][u], dist[v][i] + dist[i][u]);
            }
        }
    }
}


int main() {
    int n;
    cin >> n;
    // vvi graph(n + 1);
    vvi dist(n + 1);
    for (int i = 0; i < n + 1; i++) {
        // graph[i].resize(n + 1, 1);
        dist[i].resize(n + 1, INF);
    }
    for (int u = 1; u < n + 1; u++) {
        for (int v = 1; v < n + 1; v++) {
            cin >> dist[u][v];
        }
    }
    floyd(dist, n);
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
}
