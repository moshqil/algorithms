#include <iostream>
#include <vector>
#include <variant>
#include <execution>
#include <algorithm>
using namespace std;
using vi = vector<int>;

struct ComputeRequest { int left; int right; };

struct UpdateRequest { int index; int delta; };

using Request = variant<ComputeRequest, UpdateRequest>;

int prefix_sum(int r, const vi& f) {
    if (r < 0) {return 0;}
    int res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
        res += f[i];
    }
    return res;
}

int req(int l, int r, const vi& f) {
    return prefix_sum(r, f) - prefix_sum(l - 1, f);
}

void update(int x, int d, int n, vi& f) {
    for (int i = x; i < n; i = i | (i + 1)) {
        f[i] += d;
    }
}

vector<int> ProcessRequests(const vector<int>& numbers, const vector<Request>& requests) {
    vi f(numbers.size(), 0);
    for (int i = 0; i < numbers.size(); i++) {
        update(i, numbers[i], numbers.size(), f);
    }
    vi res(requests.size());
    auto i1 = requests.begin();
    int written = 0;
    while (i1 != requests.end()) {
        if (i1->index() == 0) {
            auto i2 = i1;
            while (i2 != requests.end() && i2->index() == 0) {
                i2++;
            }
            transform(execution::par, i1, i2, res.begin() + written,
                      [&f](const Request& request) {
                          return req(get<ComputeRequest>(request).left, get<ComputeRequest>(request).right - 1, f);
                      });
            written += i2 - i1;
            i1 = i2;
        }
        while (i1 != requests.end() && i1->index() == 1) {
            auto request = *i1;
            int ind = get<UpdateRequest>(request).index;
            int delta = get<UpdateRequest>(request).delta;
            update(ind, delta, numbers.size(), f);
            i1++;
        }
    }
    res.resize(written);
    return res;
}
