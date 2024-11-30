// problem statement: https://codeforces.com/contest/1185/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr double EPS = 1e-9;

int n;
vector<pair<int, int>> a;
map<int, int> interval;

int operator-(const pair<int, int> &a, const pair<int, int> &b) { return a.first - b.first; }

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i + 1 < n; i++) { interval[a[i + 1] - a[i]]++; }
    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            interval[a[i] - a[i - 1]]--;
            if (interval[a[i] - a[i - 1]] == 0) { interval.erase(a[i] - a[i - 1]); }
        }
        if (i + 1 < n) {
            interval[a[i + 1] - a[i]]--;
            if (interval[a[i + 1] - a[i]] == 0) { interval.erase(a[i + 1] - a[i]); }
        }
        if (i > 0 && i + 1 < n) { interval[a[i + 1] - a[i - 1]]++; }
        if (interval.size() == 1 || interval.size() == 0) {
            ans = a[i].second;
            break;
        }
        if (i > 0) { interval[a[i] - a[i - 1]]++; }
        if (i + 1 < n) { interval[a[i + 1] - a[i]]++; }
        if (i > 0 && i + 1 < n) {
            interval[a[i + 1] - a[i - 1]]--;
            if (interval[a[i + 1] - a[i - 1]] == 0) { interval.erase(a[i + 1] - a[i - 1]); }
        }
    }
    cout << ans << '\n';
    return 0;
}
