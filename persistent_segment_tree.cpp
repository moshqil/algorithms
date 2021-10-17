#include <iostream>
#include <vector>
#include <set>
using namespace std;
using vi = vector<int>;

struct node {
    int value;
    node * l_child;
    node * r_child;
};

node* build(int vl, int vr, vi& b) {
    if (vl + 1 == vr) {
        return new node{b[vl], nullptr, nullptr};
    }
    int vm = (vr + vl) / 2;
    node * l_child = build(vl, vm, b);
    node * r_child = build(vm, vr, b);
    return new node{l_child->value + r_child->value, l_child, r_child};
}

int get(int vl, int vr, node * now, int k) {
    if (now->value < k) {
        return 0;
    }
    if (now->value == 1 && vl + 1 == vr) {
        return vr;
    }
    int vm = (vl + vr) / 2;
    if (now->l_child->value >= k) {
        return get(vl, vm, now->l_child, k);
    }
    return get(vm, vr, now->r_child, k - now->l_child->value);
}

node * update(int ind, int x, node * now, int vl, int vr) {
    if (ind < vl || ind >= vr) {
        return now;
    }
    if (ind == vl && vl + 1 == vr) {
        return new node{x, nullptr, nullptr};
    }
    int vm = (vl + vr) / 2;
    node * l_child = update(ind, x, now->l_child, vl, vm);
    node * r_child = update(ind, x, now->r_child, vm, vr);
    return new node{l_child->value + r_child->value, l_child, r_child};
}

int main() {
    int n, m; cin >> n >> m;
    vi next(n, -1), last(m + 1, -1), a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        next[i] = last[a[i]];
        last[a[i]] = i;
    }
    vi b(n, 0);
    set<int> repeated;
    for (int i = 0; i < n; i++) {
        if (repeated.find(a[i]) == repeated.end()) {
            b[i] = 1;
            repeated.insert(a[i]);
        }
    }
    vector<node*> root_versions;
    node* first_root = build(0, n, b);
    root_versions.push_back(first_root);
    for (int l = 0; l < n; l++) {
        node * new_root = update(l, 0, root_versions[root_versions.size() - 1], 0, n);
        if (next[l] != -1) {
            new_root = update(next[l], 1, new_root, 0, n);
        }
        root_versions.push_back(new_root);
    }
    int q; cin >> q;
    int p = 0;
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        int l = (x + p) % n;
        int k = (y + p) % m + 1;
        int r = get(0, n, root_versions[l], k);
        cout << r << endl;
        p = r;
    }
}
