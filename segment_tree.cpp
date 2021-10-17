// RSQ with updates

#include <iostream>
#include <vector>
using namespace std;
using vi = vector<long long>;


int m(int vl, int vr) {return (vl + vr) / 2;}

int left(int v) {return 2 * v + 1;}

int right(int v) {return 2 * v + 2;}

void build(vi& tree, vi& a, int l, int r, int v) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    build(tree, a, l, m(l, r), left(v));
    build(tree, a, m(l, r), r, right(v));
    tree[v] = tree[left(v)] + tree[right(v)];
}

long long query(vi& tree, int l, int r, int v, int vl, int vr) {
    if (vl >= r || vr <= l) {return 0;}
    if (l <= vl && vr <= r) {return tree[v];}
    return query(tree, l, r, left(v), vl, m(vl, vr)) + query(tree, l, r, right(v), m(vl, vr), vr);
}

void update(vi& tree, int v, int vl, int vr, int i, int x) {
    if (vl > i || vr <= i) {return;}
    if (vl + 1 == vr && vl == i) {
        tree[v] = x;
        return;
    }
    update(tree, left(v), vl, m(vl, vr), i, x);
    update(tree, right(v), m(vl, vr), vr, i, x);
    tree[v] = tree[left(v)] + tree[right(v)];
}

int main() {
    int n; cin >> n;
    vi a(n);
    vi tree(4 * n);
    for (int i = 0; i < n; i++) {cin >> a[i];}
    build(tree, a, 0, n, 0);
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int c, l, r; cin >> c >> l >> r;
        if (c == 1) {
            cout << query(tree, l, r + 1, 0, 0, n) << endl;
        } else {
            update(tree, 0, 0, n, l, r);
        }
    }
}
