#include <iostream>
#include <vector>
#include <complex>
using namespace std;
const long double PI = acos(-1);
using cmp = complex<long double>;
using vi = vector<cmp>;
long long LEN = 524288; // все массивы константной длины
const long long N_REV = 7340019;


vi fft(vi& a, long long n, cmp w) {
    if (n == 1) {
        return {a[0]};
    }
    vi a0(a.size() / 2), a1(a.size() / 2), vals(a.size());
    for (int i = 0; i < a.size(); i += 2) {
        a0[i / 2] = a[i];
    }
    for (int i = 1; i < a.size(); i += 2) {
        a1[i / 2] = a[i];
    }
    vi vals0 = fft(a0, n / 2, w * w);
    vi vals1 = fft(a1, n / 2, w * w);
    cmp w_deg = 1;
    for (int i = 0; i < n; i++) {
        cmp new_val = (vals0[i % (n / 2)] + w_deg * vals1[i % (n / 2)]);
        w_deg *= w;
        vals[i] = new_val;
    }
    return vals;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    //s1 = '1';
    //s2 = '1';
    //for (int i = 0; i < 1; i++) {
    //    s1 += '0';
    //    s2 += '0';
    //}
    vi a(LEN, 0), b(LEN, 0);
    int coef = 1;
    if (s1[0] == '-') {
        coef *= -1;
        s1.erase(s1.begin());
    }
    if (s2[0] == '-') {
        coef *= -1;
        s2.erase(s2.begin());
    }
    cmp W{cos(2*PI/LEN), sin(2*PI/LEN)};
    for (int i = 0; i < s1.size(); i++) {
        a[i] = s1[s1.size() - 1 - i] - '0';
    }
    for (int i = 0; i < s2.size(); i++) {
        b[i] = s2[s2.size() - 1 - i] - '0';
    }
    vi a_val = fft(a, LEN, W);
    //for (auto& elem : a_val) {
    //    cout << elem << endl;
    //}
    vi b_val = fft(b, LEN, W);
    vi c_val(a_val.size());
    for (int i = 0; i < c_val.size(); i++) {
        c_val[i] = (a_val[i] * b_val[i]);
    }
    vi c_coef = fft(c_val, LEN, conj(W));
    for (int i = 0; i < c_coef.size(); i++) {
        c_coef[i] = c_coef[i] / (long double)LEN;
        c_coef[i] = round(c_coef[i].real());
    }
    vi new_new_coef;
    bool zeroes = true;
    for (int i = c_coef.size() - 1; i >= 0; i--) {
        if (c_coef[i].real() != 0) {
            zeroes = false;
        }
        if (!zeroes) {
            new_new_coef.push_back(c_coef[i]);
        }
    }
    vi new_coef;
    for (int i = new_new_coef.size() - 1; i >= 0; i--) {
        new_coef.push_back(new_new_coef[i]);
    }
    //for (auto& elem : new_coef) {
    //    cout << elem << ' ';
    //}
    //cout << endl;
    //cout << '!' << endl;
    vector<int> final_result;
    int cur = 0;
    for (auto& elem : new_coef) {
        cur += (int)(elem.real());
        final_result.push_back(cur % 10);
        cur /= 10;
    }
    while (cur != 0) {
        final_result.push_back(cur % 10);
        cur /= 10;
    }
    if (final_result.empty()) {
        cout << 0 << endl;
        return 0;
    }
    if (coef == -1) {
        cout << '-';
    }
    for (int i = final_result.size() - 1; i >= 0; i--) {
        cout << final_result[i];
    }
    cout << endl;
    //for (auto& elem : new_coef) {
    //    cout << elem << ' ';
    //}
}
