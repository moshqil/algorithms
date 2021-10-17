// treap for two operations
// 1. find min in [l, r]
// 2. reverse elements in [l, r]

#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;
const int INF = 1000000001;

struct node {
    int x, y;
    int key;
    bool reversed = false;
    int min = key;
    node* l_child = nullptr;
    node* r_child = nullptr;
};

int get_size(node* root) {
    if (root == nullptr) {return 0;}
    return root->x;
}

int get_min(node* root) {
    if (root == nullptr) {return INF;}
    return root->min;
}

void update(node* root) {
    root->x = get_size(root->l_child) + get_size(root->r_child) + 1;
    root->min = min(min(get_min(root->l_child), get_min(root->r_child)), root->key);
}

void make_reversed(node* root) {
    if (root == nullptr) {return;}
    if (root->reversed) {
        root->reversed = false;
        return;
    }
    root->reversed = true;
}

void push(node* root) {
    if (root == nullptr) {return;}
    if (!root->reversed) {return;}
    auto l = root->l_child; auto r = root->r_child;
    root->l_child = r; root->r_child = l;
    root->reversed = false;
    make_reversed(root->l_child);
    make_reversed(root->r_child);
}

node* merge(node* left, node* right) {
    push(left);
    push(right);
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->y > right->y) {
        // cout << left->key << ' ' << right-> key << endl;
        left->r_child = merge(left->r_child, right);
        update(left);
        return left;
    }
    // cout << left->key << ' ' << right-> key << endl;
    right->l_child = merge(left, right->l_child);
    update(right);
    return right;
}


pair<node*, node*> split(node*& root, int x_key) {
    push(root);
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (get_size(root->l_child) >= x_key) {
        auto p = split(root->l_child, x_key);
        root->l_child = p.second;
        update(root);
        return {p.first, root};
    }
    auto p = split(root->r_child, x_key - get_size(root->l_child) - 1);
    root->r_child = p.first;
    update(root);
    return {root, p.second};
}

void segment(node* root, int i, int j, node*& l, node*& m, node*& r) {
    --i; --j;
    auto p = split(root, j + 1);
    auto t = split(p.first, i);
    l = t.first; m = t.second; r = p.second;
}


int min_seg(node*& root, int i, int j) {
    node* n1 = nullptr;
    node* n2 = nullptr;
    node* n3 = nullptr;
    segment(root, i, j, n1, n2, n3);
    int ans = get_min(n2);
    root = merge(merge(n1, n2), n3);
    return ans;
}

void rev(node*& root, int i, int j) {
    node* n1 = nullptr;
    node* n2 = nullptr;
    node* n3 = nullptr;
    segment(root, i, j, n1, n2, n3);
    make_reversed(n2);
    root = merge(merge(n1, n2), n3);
}

void path(node* root) {
    if (root == nullptr) {
        return;
    }
    path(root->l_child);
    //cout << '(' << root->key << ' ' << root->x << ')' << ' ';
    cout << root->key << ' ';
    path(root->r_child);
}

int main() {
    int n, m;
    cin >> n >> m;
    node* root = nullptr;
    for (int i = 1; i < n + 1; i++) {
        int a; cin >> a;
        node* nn = new node {1, rand(), a};
        root = merge(root, nn);
    }
    for (int i = 0; i < m; i++) {
        int c, l, r;
        cin >> c >> l >> r;
        if (c == 1) {
            rev(root, l, r);
        } else {
            cout << min_seg(root, l, r) << endl;
        }
        //path(p.first); cout << endl;
        //path(p.second); cout << endl;
        //path(root); cout << endl;
    }
    // path(root);
}

