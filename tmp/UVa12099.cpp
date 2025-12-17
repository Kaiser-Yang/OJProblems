#include <bits/stdc++.h>

using namespace std;

struct Book {
    int h, w;
    bool operator<(const Book &other) { return h > other.h; }
};

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    vector<Book> book;
    vector<int> sumW;
    vector<vector<vector<int>>> dp;
    cin >> T;
    while (T--) {
        cin >> n;
        book.resize(n + 1);
        for (int i = 1; i <= n; i++) { cin >> book[i].h >> book[i].w; }
        sort(book.begin() + 1, book.end());
        sumW.clear();
        sumW.resize(n + 1);
        for (int i = 1; i <= n; i++) { sumW[i] = sumW[i - 1] + book[i].w; }
        dp.clear();
        dp.resize(2);
        for (int i = 0; i < 2; i++) {
            dp[i].resize(sumW[n] + 1);
            for (int j = 0; j <= sumW[n]; j++) {
                dp[i][j].resize(sumW[n] + 1, numeric_limits<int>::max());
            }
        }
        int now = 0, nex = 1;
        dp[now][0][0] = 0;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= sumW[i] - sumW[1]; j++) {
                for (int k = 0; k <= sumW[i] - sumW[1]; k++) {
                    if (i + j > sumW[i] - sumW[1]) { break; }
                    if (j > sumW[i] - j - k + 30) { break; }
                    if (k > j + 30) { break; }
                    if (dp[now][j][k] == numeric_limits<int>::max()) { continue; }
                    dp[nex][j][k] = min(dp[nex][j][k], dp[now][j][k]);
                    dp[nex][j + book[i].w][k] =
                        min(dp[nex][j + book[i].w][k], dp[now][j][k] + (j == 0 ? book[i].h : 0));
                    dp[nex][j][k + book[i].w] =
                        min(dp[nex][j][k + book[i].w], dp[now][j][k] + (k == 0 ? book[i].h : 0));
                }
            }
            swap(now, nex);
            for (int j = 0; j <= sumW[n]; j++) {
                for (int k = 0; k <= sumW[n]; k++) { dp[nex][j][k] = numeric_limits<int>::max(); }
            }
        }
        int ans = numeric_limits<int>::max();
        for (int j = 1; j <= sumW[n] - sumW[1]; j++) {
            for (int k = 1; k <= sumW[n] - sumW[1]; k++) {
                if (dp[now][j][k] == numeric_limits<int>::max()) { continue; }
                ans = min(ans, (dp[now][j][k] + book[1].h) * max(sumW[n] - j - k, max(j, k)));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
