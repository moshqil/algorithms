#include <iostream>
#include <algorithm>
#include <execution>
#include <vector>
#include <limits>
using namespace std;
using vi = vector<int>;

struct Request { int left; int right; };

int m(int vl, int vr) {return (vl + vr) / 2;}

int left(int v) {return 2 * v + 1;}

int right(int v) {return 2 * v + 2;}

void build(vi& tree, const vi& a, int l, int r, int v) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    build(tree, a, l, m(l, r), left(v));
    build(tree, a, m(l, r), r, right(v));
    tree[v] = min(tree[left(v)], tree[right(v)]);
}

int query(vi& tree, int l, int r, int v, int vl, int vr) {
    if (vl >= r || vr <= l) {return INT_MAX;}
    if (l <= vl && vr <= r) {return tree[v];}
    return min(query(tree, l, r, left(v), vl, m(vl, vr)), query(tree, l, r, right(v), m(vl, vr), vr));
}

vector<int> ProcessRequests(const vector<int>& numbers, const vector<Request>& requests) {
    vi tree(4 * numbers.size());
    build(tree, numbers, 0, numbers.size(), 0);
    vi res(requests.size());
    transform(execution::par, requests.begin(), requests.end(), res.begin(),
              [&tree, &numbers](const Request& request) {
                  return query(tree, request.left, request.right, 0, 0, numbers.size());
              });
    return res;
}
