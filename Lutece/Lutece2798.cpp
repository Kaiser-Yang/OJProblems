#include <bits/stdc++.h>

using namespace std;

int n, c;
vector<int> value, weight;
int dp[50005];

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> c;
    value.resize(n + 1);
    weight.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> value[i]; }
    for (int i = 1; i <= n; i++) { cin >> weight[i]; }
    for (int i = 1; i <= n; i++) {
        for (int j = c; j >= weight[i]; j--) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[c] << endl;
    return 0;
}