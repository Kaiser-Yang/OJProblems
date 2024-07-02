// problem statement: https://www.luogu.com.cn/problem/P2627

#include <bits/stdc++.h>

constexpr int MAXN = 1e5 + 10;

using namespace std;

int n, k;
long long sum[MAXN], dp[MAXN];
deque<long long> dq;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && dp[i - 1] - sum[i] >= dp[dq.back()] - sum[dq.back() + 1]) {
            dq.pop_back();
        }
        dq.push_back(i - 1);
        while (!dq.empty() && i - dq.front() - 1 > k) { dq.pop_front(); }
        dp[i] = dp[dq.front()] - sum[dq.front() + 1] + sum[i];
        if (i <= k) { dp[i] = max(dp[i], sum[i] - sum[max(0, i - k)]); }
    }
    cout << dp[n] << '\n';
    return 0;
}
