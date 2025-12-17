#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int S, N, M;
    vector<int> denomination;
    vector<int> dp;
    while (cin >> S && S != 0) {
        cin >> N;
        int ans1 = -1;
        vector<int> ansTemp, ans;
        while (N--) {
            cin >> M;
            denomination.resize(M);
            vector<int> origin;
            for (int i = 0; i < M; i++) {
                cin >> denomination[i];
                origin.push_back(denomination[i]);
            }
            sort(denomination.begin(), denomination.end(), greater<int>());
            dp.clear();
            dp.resize(100 * S + 1, numeric_limits<int>::max() / 10);
            dp[0] = 0;
            for (int i = 1; i < dp.size(); i++) {
                for (int j = 0; j < M; j++) {
                    if (i - denomination[j] >= 0) {
                        dp[i] = min(dp[i], dp[i - denomination[j]] + 1);
                    }
                }
                if (dp[i] > S) {
                    if (i - 1 > ans1) {
                        ans1 = i - 1;
                        ansTemp.swap(denomination);
                        ans.swap(origin);
                    } else if (i - 1 == ans1) {
                        if (M < (int)ansTemp.size()) {
                            ansTemp.swap(denomination);
                            ans.swap(origin);
                        } else if (M == (int)ansTemp.size()) {
                            bool ok = false;
                            for (int k = 0; k < M; k++) {
                                if (denomination[k] < ansTemp[k]) {
                                    ok = true;
                                    break;
                                } else if (denomination[k] > ansTemp[k]) {
                                    break;
                                }
                            }
                            if (ok) {
                                ansTemp.swap(denomination);
                                ans.swap(origin);
                            }
                        }
                    }
                    break;
                }
            }
        }
        cout << "max coverage = " << setw(3) << ans1 << " :";
        for (auto num : ans) { cout << setw(3) << num; }
        cout << endl;
    }
    return 0;
}
