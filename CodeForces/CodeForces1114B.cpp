// problem statement: https://codeforces.com/contest/1114/problem/B

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<pair<int, int>> a;
map<int, int> cnt;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
        cnt[a[i].first]++;
    }
    long long sum = 0;
    for (auto& p : a) {
        sum += p.first;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n - m * k; i++) {
        cnt[a[i].first]--;
        sum -= a[i].first;
    }
    sort(a.begin(), a.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.second < y.second;
    });
    cout << sum << '\n';
    int now_chosen = 0, total_block = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[a[i].first] == 0) { continue; }
        cnt[a[i].first]--;
        now_chosen++;
        if (now_chosen == m) {
            cout << i + 1 << ' ';
            now_chosen = 0;
            total_block++;
        }
        if (total_block == k - 1) { break; }
    }
    return 0;
}
