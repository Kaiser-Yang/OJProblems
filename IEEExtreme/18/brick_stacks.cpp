// problem statement: https://csacademy.com/contest/ieeextreme-practice/task/brick-stacks/

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e6 + 10;

int n, x;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> x;
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    sort(a, a + n);
    int ans = 1;
    vector<vector<int>> pile;
    pile.push_back({a[0]});
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({a[0], ans - 1});
    for (int i = 1; i < n; i++) {
        auto min_val = q.top();
        if (min_val.first + x <= a[i]) {
            q.pop();
            q.push({a[i], min_val.second});
            pile[min_val.second].push_back(a[i]);
        } else {
            ans++;
            q.push({a[i], ans - 1});
            pile.push_back({a[i]});
        }
    }
    cout << ans << endl;
    for (int i = 0; i < ans; i++) {
        cout << pile[i].size() << " ";
        reverse(pile[i].begin(), pile[i].end());
        for (auto &&ele : pile[i]) { cout << ele << " "; }
        cout << endl;
    }
    return 0;
}
