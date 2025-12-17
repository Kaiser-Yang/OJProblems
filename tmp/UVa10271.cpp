#include <bits/stdc++.h>

using namespace std;

int T, K, N;
vector<int> chopstick;
vector<vector<int>> d;
constexpr int INF = numeric_limits<int>::max();

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> K >> N;
        K += 8;
        chopstick.resize(N + 1);
        for (int i = N; i >= 1; i--) { cin >> chopstick[i]; }
        d.clear();
        d.resize(N + 1);
        for (int i = 0; i <= N; i++) {
            d[i].resize(K + 1, INF);
            d[i][0] = 0;
        }
        for (int i = 3; i <= N; i++) {
            for (int j = 1; j <= K && 3 * j <= i; j++) {
                d[i][j] = d[i - 1][j];
                if (d[i - 2][j - 1] != INF) {
                    d[i][j] = min(d[i][j], d[i - 2][j - 1] + (chopstick[i] - chopstick[i - 1]) * (chopstick[i] - chopstick[i - 1]));
                }
            }
        }
        cout << d[N][K] << endl;
    }
    return 0;
}
