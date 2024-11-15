// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXM = 1e2 + 10;

int L, S, T, M, ans = std::numeric_limits<int>::max();
set<int> hasStone;
vector<int> dp;
int stonePos[MAXM];

int main() {
    cin >> L >> S >> T >> M;
    for (int i = 1; i <= M; i++) { cin >> stonePos[i]; }
    stonePos[0] = 0;
    stonePos[M + 1] = L;
    sort(stonePos + 1, stonePos + 1 + M);
    int pos = 0;
    for (int i = 1; i <= M + 1; i++) {
        if (stonePos[i] - stonePos[i - 1] > T) {
            pos += (stonePos[i] - stonePos[i - 1]) % T + T;
        } else {
            pos += stonePos[i] - stonePos[i - 1];
        }
        hasStone.insert(pos);
    }
    hasStone.erase(pos);  // there is no stone at the end point.
    dp.resize(pos + 1, std::numeric_limits<int>::max() / 2);
    dp[0] = 0;
    for (int i = 1; i <= pos; i++) {
        for (int j = max(0, i - T); j <= max(-1, i - S); j++) {
            dp[i] = min(dp[i], dp[j] + (int)hasStone.count(i));
        }
    }
    for (int j = max(0, pos - T); j <= pos; j++) { ans = min(ans, dp[j]); }
    cout << ans << endl;
    return 0;
}