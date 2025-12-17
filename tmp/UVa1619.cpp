#include <bits/stdc++.h>

using namespace std;

bool check(int i, int n, bool reverse) {
    if (reverse) {
        return i >= 1;
    } else {
        return i <= n;
    }
}

void init(vector<int> &res, vector<int> &a, bool reverse) {
    int n = a.size() - 1;
    stack<int> number;
    int i = 1;
    if (reverse) { i = n; }
    for (; check(i, n, reverse);) {
        vector<int> p;
        while (!number.empty() && a[i] <= a[number.top()]) {
            if (a[i] == a[number.top()]) { p.push_back(number.top()); }
            number.pop();
        }
        if (number.empty()) {
            res[i] = 0;
            if (reverse) { res[i] = n + 1; }
        } else {
            res[i] = number.top();
        }
        if (p.empty()) {
            number.push(i);
        } else {
            number.push(p.back());
            number.push(i);
        }
        if (reverse) {
            i--;
        } else {
            i++;
        }
    }
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    int n;
    bool first = true;
    vector<int> a, l, r;
    vector<long long> sum;
    while (cin >> n) {
        a.resize(n + 1);
        l.resize(n + 1);
        r.resize(n + 1);
        sum.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        init(l, a, false);
        init(r, a, true);
        long long ans = a[1];
        int ansLeft = 1, ansRight = 1;
        for (int i = 1; i <= n; i++) {
            int right = r[i] - 1, left = l[i] + 1;
            if ((sum[right] - sum[left - 1]) * a[i] > ans) {
                ans = (sum[right] - sum[left - 1]) * a[i];
                ansLeft = left;
                ansRight = right;
            }
        }
        if (!first) { cout << endl; }
        cout << ans << endl;
        cout << ansLeft << " " << ansRight << endl;
        first = false;
    }
    return 0;
}
