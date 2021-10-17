#include <iostream>
#include <vector>
using namespace std;

struct snowball {
    long long m = 0;
    snowball * previous = nullptr;
};

int main() {
    vector<snowball*> versions;
    snowball first = {0, nullptr};
    versions.push_back(&first);
    long long sum = 0;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        long long t, m; cin >> t; cin >> m;
        if (m == 0) {
            versions.push_back(versions[t]->previous);
        } else {
            versions.push_back(new snowball{versions[t]->m + m, versions[t]});
        }
        sum += versions[versions.size() - 1]->m;
    }
    cout << sum << endl;
};
