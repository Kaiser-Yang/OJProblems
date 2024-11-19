// problem statement: https://codeforces.com/problemset/problem/2038/G

#include <bits/stdc++.h>

using namespace std;

int T, n;

void guess(int i, int val) {
    cout << "0 " << i << " " << val << '\n';
    cout.flush();
    int res;
    cin >> res;
    if (res != 1) {
        exit(-1);
    }
}

int query(const string &str) {
    cout << "1 " << str << '\n';
    cout.flush();
    int res;
    cin >> res;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        int cnt0 = query("0");
        int cnt1 = n - cnt0;
        int cnt = cnt0 - query("00");
        int cnt10 = query("10");
        if (cnt10 == cnt) {
            guess(1, 1);
        } else {
            guess(1, 0);
        }
    }
    return 0;
}
