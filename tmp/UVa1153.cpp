#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<pair<int, int>> time;
    cin >> T;
    bool first = true;
    while (T--) {
        cin >> n;
        time.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> time[i].first >> time[i].second;
        }
        sort(time.begin(), time.end(), [] (const pair<int, int> &lhs, const pair<int, int> &rhs) {
            if (lhs.second == rhs.second) { return lhs.first < rhs.first; }
            return lhs.second < rhs.second;
        });
        int lastEndTime = 0;
        priority_queue<int> q;
        for (int i = 0; i < n; i++) {
            if (lastEndTime + time[i].first <= time[i].second) {
                q.push(time[i].first);
                lastEndTime += time[i].first;
            } else {
                if (q.empty()) { continue; }
                int top = q.top();
                if (time[i].first < top) {
                    lastEndTime -= top - time[i].first;
                    q.pop();
                    q.push(time[i].first);
                }
            }
        }
        if (!first) { cout << endl; }
        cout << q.size() << endl;
        first = false;
    }
    return 0;
}
