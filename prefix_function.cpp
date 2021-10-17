#include <iostream>
#include <vector>
using namespace std;
using vi = vector<int>;

void prefix_f(string& s, vi& prefix) {
    for (int i = 1; i < prefix.size(); i++) {
        int p = prefix[i - 1];
        while (p > 0 && s[i] != s[p]) {
            p = prefix[p - 1];
        }
        if (s[i] == s[p]) {
            prefix[i] = p + 1;
        }
    }
}

int main() {
    string s; cin >> s;
    vi prefix(s.size(), 0);
    prefix_f(s, prefix);
    for (auto& elem : prefix) {
        cout << elem << ' ';
    }
    cout << endl;
}
