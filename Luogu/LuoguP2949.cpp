// problem statement: https://www.luogu.com.cn/problem/P2949

#include <bits/stdc++.h>

constexpr int MAXN = 1e5 + 10;

using namespace std;

int n;
long long ans;

pair<int, int> task[MAXN];
priority_queue<int, vector<int>, greater<int>> q;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> task[i].second >> task[i].first; }
    sort(task, task + n, [](const auto &a, const auto &b) {
        if (a.second != b.second) { return a.second < b.second; }
        return a.first > b.first;
    });
    int nowTime = 0;
    for (int i = 0; i < n; i++) {
        if (nowTime < task[i].second) {
            nowTime++;
            ans += task[i].first;
            q.push(task[i].first);
        } else if (!q.empty() && q.top() < task[i].first) {
            ans -= q.top();
            ans += task[i].first;
            q.pop();
            q.push(task[i].first);
        }
    }
    cout << ans << "\n";
    return 0;
}
