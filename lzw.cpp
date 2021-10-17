#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
using vi = vector<int>;

vi encode(unordered_map<string, int>& dict, string& s) {
    int max_val = 128;
    vi result;
    string subs;
    for (auto& elem : s) {
        string elem_s; elem_s += elem;
        if (dict[subs + elem] != 0) {
            subs += elem;
            continue;
        }
        dict[subs + elem] = max_val++;
        //cout << subs + elem << ' ' << dict[subs + elem] << endl;
        result.push_back(dict[subs]);
        //cout << subs << ' '<< dict[subs] << endl;
        //cout << elem_s << ' '<< dict[elem_s] << endl;
        subs = elem_s;
    }
    if (!subs.empty()) {
        result.push_back(dict[subs]);
    }
    return result;
}

string decode(unordered_map<int, string>& dict, vi& encoded) {
    string result = dict[encoded[0]];
    int max_value = 128;
    for (int i = 1; i < encoded.size(); i++) {
        if (dict[encoded[i]] == "") {
            dict[max_value++] = dict[encoded[i - 1]] + dict[encoded[i - 1]][0];
        } else {
            dict[max_value++] = dict[encoded[i - 1]] + dict[encoded[i]][0];
        }
        //cout << dict[max_value - 1] << ' ' << max_value - 1 << endl;
        //cout << dict[encoded[i]] << ' ' << encoded[i] << endl;
        result += dict[encoded[i]];
    }
    return result;
}
