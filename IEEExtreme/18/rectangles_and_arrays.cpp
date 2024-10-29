// problem statement:
// https://csacademy.com/ieeextreme-practice/task/rectangles-and-arrays-ieeextreme-18

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e6 + 10;

int n, x;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> x;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    vector<int> l1(n + 1), r1(n + 1), l2(n + 1), r2(n + 1), l3(n + 1), r3(n + 1);
    stack<int> s, s1, s2, s3;
    for (int i = 1; i <= n; i++) {
        while (!s.empty() && a[s.top()] >= a[i]) { s.pop(); }
        l1[i] = (s.empty() ? 0 : s.top());
        s.push(i);
    }
    while (!s.empty()) { s.pop(); }
    for (int i = n; i >= 1; i--) {
        while (!s.empty() && a[s.top()] >= a[i]) { s.pop(); }
        r1[i] = (s.empty() ? n + 1 : s.top());
        s.push(i);
    }
    for (int i = n; i >= 1; i--) {
        while (!s2.empty() && a[s2.top()] > a[i]) {
            l2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && a[s1.top()] >= a[i]) {
            s3.push(s1.top());
            s1.pop();
        }
        s1.push(i);
        while (!s3.empty()) {
            s2.push(s3.top());
            s3.pop();
        }
    }
    while (!s1.empty()) {
        l2[s1.top()] = 0;
        s1.pop();
    }
    while (!s2.empty()) {
        l2[s2.top()] = 0;
        s2.pop();
    }
    while (!s3.empty()) { s3.pop(); }
    for (int i = 1; i <= n; i++) {
        while (!s2.empty() && a[s2.top()] > a[i]) {
            r2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && a[s1.top()] >= a[i]) {
            s3.push(s1.top());
            s1.pop();
        }
        s1.push(i);
        while (!s3.empty()) {
            s2.push(s3.top());
            s3.pop();
        }
    }
    while (!s1.empty()) {
        r2[s1.top()] = n + 1;
        s1.pop();
    }
    while (!s2.empty()) {
        r2[s2.top()] = n + 1;
        s2.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (x < a[i]) {
            l2[i] = l1[i];
            r2[i] = r1[i];
        }
    }
    while (!s.empty()) { s.pop(); }
    for (int i = 1; i <= n; i++) {
        queue<int> now_pop;
        while (!s.empty() && a[s.top()] >= x) {
            now_pop.push(s.top());
            s.pop();
        }
        l3[i] = (s.empty() ? 0 : s.top());
        while (!now_pop.empty()) {
            s.push(now_pop.front());
            now_pop.pop();
        }
        while (!s.empty() && a[s.top()] >= a[i]) { s.pop(); }
        s.push(i);
    }
    while (!s.empty()) { s.pop(); }
    for (int i = n; i >= 1; i--) {
        queue<int> now_pop;
        while (!s.empty() && a[s.top()] >= x) {
            now_pop.push(s.top());
            s.pop();
        }
        r3[i] = (s.empty() ? n + 1 : s.top());
        while (!now_pop.empty()) {
            s.push(now_pop.front());
            now_pop.pop();
        }
        while (!s.empty() && a[s.top()] >= a[i]) { s.pop(); }
        s.push(i);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max({ans,
                   1LL * (r1[i] - l1[i] - 1) * a[i],
                   1LL * (r2[i] - l1[i] - 1) * a[i],
                   1LL * (r1[i] - l2[i] - 1) * a[i],
                   1LL * (r3[i] - l3[i] - 1) * x});
    }
    cout << ans << endl;
    return 0;
}
