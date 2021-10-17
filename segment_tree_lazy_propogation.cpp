// RSQ with segment updates

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vi = vector<long long>;


struct node {
    long long x;
    long long add;
};
using vn = vector<node>;

void push(vn& tree, int v, int vl, int vr) {
    if (vl + 1 == vr) {
        tree[v].x += tree[v].add;
        tree[v].add = 0;
        return;
    }
    tree[2 * v + 1].add += tree[v].add;
    tree[2 * v + 2].add += tree[v].add;
    tree[v].x += tree[v].add * (vr - vl);
    tree[v].add = 0;
}


void build(vn& tree, vi& a, int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {a[l], 0};
        return;
    }
    build(tree, a, 2 * v + 1, l, (l + r) / 2);
    build(tree, a, 2 * v + 2, (l + r) / 2, r);
    node left = tree[2 * v + 1];
    node right = tree[2 * v + 2];
    tree[v] = {left.x + right.x, 0};
}


void mass_update(vn& tree, int v, int vl, int vr, int l, int r, int x) {
    push(tree, v, vl, vr);
    if (l <= vl && vr <= r) {
        tree[v].add += x;
        push(tree, v, vl, vr);
        return;
    }
    if (vr <= l || vl >= r) {return;}
    mass_update(tree, 2 * v + 1, vl, (vl + vr) / 2, l, r, x);
    mass_update(tree, 2 * v + 2, (vl + vr) / 2, vr, l, r, x);
    node left = tree[2 * v + 1];
    node right = tree[2 * v + 2];
    tree[v] = {left.x + right.x, 0};
}


long long query(vn& tree, int v, int vl, int vr, int l, int r) {
    push(tree, v, vl, vr);
    if (vl >= r || vr <= l) {return 0;}
    if (l <= vl && vr <= r) {return tree[v].x;}
    long long left = query(tree, 2 * v + 1, vl, (vl + vr) / 2, l, r);
    long long right = query(tree, 2 * v + 2, (vl + vr) / 2, vr, l, r);
    return left + right;
}


int main() {
    int n; cin >> n;
    vi a(n);
    vn tree(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(tree, a, 0, 0, n);
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int c; cin >> c;
        if (c == 1) {
            int l, r; cin >> l >> r;
            cout << query(tree, 0, 0, n, l, ++r) << endl;
        } else {
            int l, r, x; cin >> l >> r >> x;
            mass_update(tree, 0, 0, n, l, ++r, x);
        }
    }
}
