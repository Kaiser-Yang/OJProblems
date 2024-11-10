// problem statement: https://csacademy.com/contest/ieeextreme-practice/task/ieee754-emulator/

#include <bits/stdc++.h>

using namespace std;

union {
    float f;
    unsigned int i;
} u;

float hexstr_to_float(string hexstr) {
    stringstream ss;
    ss << hex << hexstr;
    ss >> u.i;
    return u.f;
}

string float_to_hexstr(float f) {
    u.f = f;
    stringstream ss;
    ss << hex << u.i;
    string res = ss.str();
    while (res.size() < 8) { res = '0' + res; }
    return res;
}

float bitwise_nand(float a, float b) {
    u.f = a;
    unsigned int ai = u.i;
    u.f = b;
    unsigned int bi = u.i;
    u.i = ~(ai & bi);
    return u.f;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        string c0;
        cin >> c0;
        int l;
        cin >> l;
        vector<vector<float>> lut(l);
        for (int i = 0; i < l; i++) {
            int k;
            cin >> k;
            lut[i].resize(k);
            for (int j = 0; j < k; j++) {
                string num;
                cin >> num;
                lut[i][j] = hexstr_to_float(num);
            }
        }
        int q;
        cin >> q;
        vector<float> res;
        res.push_back(hexstr_to_float(c0));
        while (q--) {
            string op;
            cin >> op;
            if (op == "L") {
                int i, j, b;
                cin >> i >> j >> b;
                u.f = res.front();
                unsigned int mask = (u.i >> j) & ((1 << b) - 1);
                res.push_back(lut[i][mask]);
            } else if (op == "N") {
                int i, j;
                cin >> i >> j;
                res.push_back(bitwise_nand(res[i], res[j]));
            } else if (op == "F") {
                int i, j, k;
                cin >> i >> j >> k;
                res.push_back(fmaf(res[i], res[j], res[k]));
            } else if (op == "C") {
                string const_value;
                cin >> const_value;
                res.push_back(hexstr_to_float(const_value));
            } else {
                return -1;
            }
        }
        cout << float_to_hexstr(res.back()) << '\n';
    }
    return 0;
}
