#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100 + 5;
constexpr int MAXM = 30 + 5;
constexpr int INF = numeric_limits<int>::max() / 10;

int N, M;
int p[MAXM], d[MAXN][MAXM];

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M && !(N == 0 && M == 0)) {
        for (int i = 1; i <= M; i++) { cin >> p[i]; }
        for (int i = 1; i <= N; i++) { d[i][0] = 0; }
        for (int j = 0; j <= M; j++) { d[0][j] = INF; }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                d[i][j] = d[i][j - 1];
                for (int k = 0; k < i; k++) {
                    d[i][j] = max(d[i][j], min(d[k][j - 1], p[j] / (i - k)));
                }
            }
        }
        if (d[N][M] == 0) {
            cout << "0 0\n";
            continue;
        }
        cout << d[N][M] << " ";
        int temp = d[N][M];
        for (int i = 1; i <= N; i++) { d[i][0] = INF; }
        for (int j = 0; j <= M; j++) { d[0][j] = 0; }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                d[i][j] = d[i][j - 1];
                for (int k = 0; k < i; k++) {
                    if (p[j] / (i - k) >= temp) { d[i][j] = min(d[i][j], d[k][j - 1] + p[j]); }
                }
            }
        }
        cout << d[N][M] << endl;
    }
    return 0;
}