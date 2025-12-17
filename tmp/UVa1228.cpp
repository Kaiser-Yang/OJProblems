#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n, delay, kase = 0;
    unsigned long long k;
    vector<int> bit;
    while (cin >> n && n != 0) {
        cin >> delay >> k;
        bit.resize(n);
        for (int i = 0; i < n; i++) {
            bit[n - i - 1] = k & 1;
            k >>= 1;
        }
        int cnt0 = 0, cnt1 = 0;
        vector<int> sendTime0, sendTime1;
        for (int i = 0; i < n; i++) {
            if (bit[i] == 0) {
                sendTime0.push_back(i);
                cnt0++;
            } else {
                sendTime1.push_back(i);
                cnt1++;
            }
        }
        vector<vector<unsigned long long>> d;
        d.resize(cnt0 + 1);
        for (int i = 0; i <= cnt0; i++)  {
            d[i].resize(cnt1 + 1);
        }
        d[0][0] = 1;
        for (int i = 0; i <= cnt0; i++) {
            for (int j = 0; j <= cnt1; j++) {
                if (i + 1 <= cnt0 && (j == cnt1 || sendTime1[j] + delay >= sendTime0[i])) { // the next one can reach after the next zero
                    d[i + 1][j] += d[i][j];
                }
                if (j + 1 <= cnt1 && (i == cnt0 || sendTime0[i] + delay >= sendTime1[j])) { // the next zero can reach after the next one
                    d[i][j + 1] += d[i][j];
                }
            }
        }
        unsigned long long minAns = 0, maxAns = 0;
        vector<pair<int, int>> reachTime;
        for (int i = 0; i < n; i++) {
            if (bit[i] == 0) {
                reachTime.push_back({i + delay, 0});
            } else {
                reachTime.push_back({i, 1});
            }
        }
        sort(reachTime.begin(), reachTime.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            if (lhs.first != rhs.first) {
                return lhs.first > rhs.first;
            }
            return lhs.second < rhs.second;
        });
        for (int i = 0; i < n; i++) {
            maxAns += 1LL * reachTime[i].second << i;
        }
        reachTime.clear();
        for (int i = 0; i < n; i++) {
            if (bit[i] == 0) {
                reachTime.push_back({i, 0});
            } else {
                reachTime.push_back({i + delay, 1});
            }
        }
        sort(reachTime.begin(), reachTime.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            if (lhs.first != rhs.first) {
                return lhs.first > rhs.first;
            }
            return lhs.second > rhs.second;
        });
        for (int i = 0; i < n; i++) {
            minAns += 1LL * reachTime[i].second << i;
        }
        cout << "Case " << ++kase << ": ";
        cout << d[cnt0][cnt1] << " " << minAns << " " << maxAns << endl;
    }
    return 0;
}