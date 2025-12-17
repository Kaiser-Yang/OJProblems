#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int N, T, M1, M2, d, e;
    vector<int> t;
    vector<vector<int>> dp;
    vector<vector<vector<bool>>> hasTrain;
    int kase = 0;
    const int INF = 1e9;
    while (cin >> N && N != 0) {
        cin >> T;
        t.resize(N);
        for (int i = 1; i < N; i++) { cin >> t[i]; }
        hasTrain.clear();
        hasTrain.resize(T + 1);
        for (int i = 0; i <= T; i++) {
            hasTrain[i].resize(N + 1);
            for (int j = 0; j <= N; j++) {
                hasTrain[i][j].resize(2, false);
                // hasTrain[t][i][0] at time t and station i, whether there are or not has a train driving to right
                // hasTrain[t][i][0] at time t and station i, whether there are or not has a train driving to left
            }
        }
        cin >> M1;
        for (int i = 0; i < M1; i++) {
            cin >> d;
            int now = d;
            for (int j = 1; j <= N; j++) {
                if (now > T) { break; }
                hasTrain[now][j][0] = true;
                now += t[j];
            }
        }
        cin >> M2;
        for (int i = 0; i < M2; i++) {
            cin >> e;
            int now = e;
            for (int j = N; j >= 1; j--) {
                if (now > T) { break; }
                hasTrain[now][j][1] = true;
                now += t[j - 1];
            }
        }
        dp.clear();
        dp.resize(T + 1);
        for (int i = 0; i <= T; i++) { dp[i].resize(N + 1, INF); }
        dp[T][N] = 0;
        for (int i = T-1; i >= 0; i--) {
            for (int j = 1; j <= N; j++) {
                dp[i][j] = dp[i + 1][j] + 1;
                if (j < N && hasTrain[i][j][0] && i + t[j] <= T) {
                    dp[i][j] = min(dp[i][j] , dp[i + t[j]][j + 1]);
                }
                if (j > 1 && hasTrain[i][j][1] && i + t[j - 1] <= T) {
                    dp[i][j] = min(dp[i][j], dp[i + t[j - 1]][j - 1]);
                }
            }
        }
        kase++;
        cout << "Case Number " << kase << ": ";
        if (dp[0][1] >= INF) {
            cout << "impossible\n";
        } else {
            cout << dp[0][1] << endl;
        }
    }
    return 0;
}
