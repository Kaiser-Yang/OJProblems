/*
    You are given n integers. Every operation, you can choose any two integers in the sequences,
remove them, and insert the sum of the selected two integers. And the cost of each operation is
the sum of the two selected integers. After n-1 operations, you will get one number, you need
output the minimum number of cost of n-1 operations.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, a;
    long long ans;
    priority_queue<long long, vector<long long>, greater<long long>> q;
    while(cin >> n && n != 0) {
        while (!q.empty()) { q.pop(); }
        ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a;
            q.push(a);
        }
        while (q.size() >= 2) {
            long long a = q.top(); q.pop();
            long long b = q.top(); q.pop();
            ans += a + b;
            q.push(a + b);
        }
        cout << ans << endl;
    }
    return 0;
}
