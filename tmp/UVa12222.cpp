#include <bits/stdc++.h>

using namespace std;

constexpr int INF = numeric_limits<int>::max() / 2;

int T, n, cntA, cntB;
vector<pair<int, int>> carA(201), carB(201);
vector<vector<vector<int>>> dp(201, vector<vector<int>>(201, vector<int>(2)));

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        cntA = cntB = 0;
        for (int i = 0; i < n; i++) {
            string name;
            int arriveTime, throughTime;
            cin >> name >> arriveTime >> throughTime;
            if (name[0] == 'A') {
                cntA++;
                carA[cntA] = {arriveTime, throughTime};
            } else {
                cntB++;
                carB[cntB] = {arriveTime, throughTime};
            }
        }
        for (int i = 0; i <= cntA; i++) {
            for (int j = 0; j <= cntB; j++) {
                dp[i][j][0] = dp[i][j][1] = INF;
            }
        }
        dp[0][0][0] = dp[0][0][1] = 0;
        for (int i = 0; i <= cntA; i++) {
            for (int j = 0; j <= cntB; j++) {
                int startTime = dp[i][j][1], maxDp = dp[i][j][1] - 10;
                for (int x = 1; i + x <= cntA; x++) {
                    startTime = max(startTime, carA[i + x].first);
                    maxDp = max(maxDp + 10, startTime + carA[i + x].second);
                    dp[i + x][j][0] = min(dp[i + x][j][0], maxDp);
                    startTime += 10;
                }
                startTime = dp[i][j][0], maxDp = dp[i][j][0] - 10;
                for (int x = 1; j + x <= cntB; x++) {
                    startTime = max(startTime, carB[j + x].first);
                    maxDp = max(maxDp + 10, startTime + carB[j + x].second);
                    dp[i][j + x][1] = min(dp[i][j + x][1], maxDp);
                    startTime += 10;
                }
            }
        }
        cout << min(dp[cntA][cntB][0], dp[cntA][cntB][1]) << endl;
    }
    return 0;
}
