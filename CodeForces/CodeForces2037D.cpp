// problem statement: https://codeforces.com/problemset/problem/2037/D

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;

int T, n, m, L;

struct {
    int l, r;
} hurdle[MAXN];

struct {
    int x, v;
} power_up[MAXM];

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n >> m >> L;
        for (int i = 1; i <= n; i++) {
            cin >> hurdle[i].l >> hurdle[i].r;
        }
        for (int i = 1; i <= m; i++) {
            cin >> power_up[i].x >> power_up[i].v;
        }
        bool ok = true;
        int power = 1, ans = 0, power_up_idx = 1;
        int las = 0;
        priority_queue<int> power_up_queue;
        for (int i = 1; i <= n; i++) {
            while (power_up_idx <= m && power_up[power_up_idx].x < hurdle[i].l) {
                power_up_queue.push(power_up[power_up_idx].v);
                power_up_idx++;
            }
            while (!power_up_queue.empty() && power <= hurdle[i].r - hurdle[i].l + 1) {
                power += power_up_queue.top();
                power_up_queue.pop();
                ans++;
            }
            if (power <= hurdle[i].r - hurdle[i].l + 1) {
                ok = false;
                break;
            }
            las = hurdle[i].r;
        }
        cout << (ok ? ans : -1) << '\n';
    }
    return 0;
}
