// problem statement: https://codeforces.com/contest/1185/problem/C2

#include <bits/stdc++.h>

using namespace std;

int n, m, sum;
vector<int> t;

priority_queue<int> q1;
priority_queue<int, vector<int>, greater<int> > q2;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    t.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> t[i]; }
    for (int i = 1; i <= n; i++) {
        if (sum + t[i] <= m) {
            while (!q2.empty() && q2.top() + t[i] + sum <= m) {
                q1.push(q2.top());
                sum += q2.top();
                q2.pop();
            }
        } else {
            while (!q1.empty()) {
                if (sum - q1.top() + t[i] > m) {
                    sum -= q1.top();
                    q2.push(q1.top());
                    q1.pop();
                } else {
                    sum -= q1.top();
                    q2.push(q1.top());
                    q1.pop();
                    break;
                }
            }
        }
        cout << q2.size() << ' ';
        if (q1.empty()) {
            q2.push(t[i]);
        } else if (t[i] >= q1.top()) {
            q2.push(t[i]);
        } else {
            q1.push(t[i]);
            sum += t[i];
        }
    }
    return 0;
}
