// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 31;
constexpr int MAXV = 200001;

int V, n;
int volume[MAXN], dp[MAXV * MAXN];

int main() {
    cin >> V >> n;
    for (int i = 1; i <= n; i++) { cin >> volume[i]; }
    for (int j = 0; j <= V; j++) { dp[j] = j; }
    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= volume[i]; j--) { dp[j] = min(dp[j], dp[j - volume[i]]); }
    }
    cout << dp[V] << endl;
    return 0;
}