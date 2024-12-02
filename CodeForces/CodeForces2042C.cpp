// problem statement: https://codeforces.com/contest/2042/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
long long k;
string s;
vector<int> cnt;

struct Comparator {
    bool operator()(int a, int b) { return cnt[a] < cnt[b]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k >> s;
        cnt.clear();
        cnt.resize(n);
        long long now = 0, ans = n;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                cnt[i]++;
                now -= i;
            } else {
                cnt[i]--;
                now += i;
            }
            if (i != n - 1) { cnt[i] += cnt[i + 1]; }
        }
        priority_queue<int, vector<int>, Comparator> q;
        for (int i = 1; i < n; i++) { q.push(i); }
        while (!q.empty()) {
            int i = q.top();
            q.pop();
            if (cnt[i] >= 0) {
                ans--;
                now += cnt[i];
            } else {
                if (now + cnt[i] >= k) {
                    ans--;
                    now += cnt[i];
                } else {
                    if (now < k) { ans = -1; }
                    break;
                }
            }
        }
        if (now < k) { ans = -1; }
        cout << ans << '\n';
    }
    return 0;
}
