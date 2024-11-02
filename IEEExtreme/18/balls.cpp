// problem statement: https://csacademy.com/ieeextreme-practice/task/balls

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXK = 100 + 10;
constexpr int LOWER_BOUND_OF_N = 200010;

long long n;
int k;

int ele[MAXK];

long long dp[MAXK][LOWER_BOUND_OF_N];

long long dfs(int i, long long now) {
    if (i == k || now == 0) { return now; }
    if (now < LOWER_BOUND_OF_N && dp[i][now] != -1) { return dp[i][now]; }
    long long res = dfs(i + 1, now) - dfs(i + 1, now / ele[i]);
    if (now < LOWER_BOUND_OF_N) { dp[i][now] = res; }
    return res;
}

int main() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    for (int i = 0; i < k; i++) { cin >> ele[i]; }
    sort(ele, ele + k, greater<int>());
    cout << n - dfs(0, n) << endl;
    return 0;
}
