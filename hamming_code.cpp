#include <iostream>
#include <vector>
using namespace std;

vector<int> encode(vector<int> s) {
    vector<int> result(1);
    int i = 1; int j = 0; int d = 0;
    while (j < s.size()) {
        if (i == (1<<d)) {
            result.push_back(0);
            i++; d++;
        } else {
            result.push_back(s[j]);
            j++; i++;
        }
    }
    d = 0;
    for (int i = 1; i < result.size(); i++) {
        if (i != (1<<d)) {
            continue;
        }
        int sum = 0;
        for (int j = i; j < result.size(); j += 2 * i) {
            for (int k = 0; k < i && (j + k) < result.size(); k++) {
                sum = (sum + result[j + k]) % 2;
            }
        }
        result[i] = sum;
        d++;
    }
    return result;
}

vector<int> decode(vector<int> encoded) {
    int error_ind = 0;
    int d = 0;
    for (int i = 1; i < encoded.size(); i++) {
        if (i != (1<<d)) {
            continue;
        }
        int sum = 0;
        for (int j = i; j < encoded.size(); j += 2 * i) {
            for (int k = 0; k < i && (j + k) < encoded.size(); k++) {
                sum = (sum + encoded[j + k]) % 2;
            }
        }
        if (sum != 0) {
            error_ind += i;
        }
        d++;
    }
    encoded[error_ind] = (encoded[error_ind] + 1) % 2;

    vector<int> result;
    d = 0;
    for (int i = 1; i < encoded.size(); i++) {
        if (i == (1<<d)) {
            d++;
            continue;
        }
        result.push_back(encoded[i]);
    }
    return result;
}
