// problem statement: https://www.luogu.com.cn/problem/P1776

#include <bits/stdc++.h>

constexpr int MAXV = 4e4 + 10;
constexpr int MAXN = 1e2 + 10;

using namespace std;

int n, v, last = 0, now = 1;
array<int, MAXN> value, volume, cnt;
deque<int> q;
array<array<int, MAXV>, 2> dp;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> v;
    for (int i = 1; i <= n; i++) { cin >> value[i] >> volume[i] >> cnt[i]; }
    for (int i = 1; i <= n; i++) {
        for (int y = 0; y < volume[i]; y++) {
            deque<int>().swap(q);
            for (int x = 0; x * volume[i] + y <= v; x++) {
                while (!q.empty() && q.front() < x - cnt[i]) { q.pop_front(); }
                while (!q.empty() && dp[last][q.back() * volume[i] + y] - q.back() * value[i] <
                                         dp[last][x * volume[i] + y] - x * value[i]) {
                    q.pop_back();
                }
                q.push_back(x);
                dp[now][x * volume[i] + y] =
                    dp[last][q.front() * volume[i] + y] - q.front() * value[i] + x * value[i];
            }
        }
        swap(last, now);
    }
    cout << dp[last][v] << endl;
    return 0;
}
