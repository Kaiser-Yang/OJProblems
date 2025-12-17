/*
    You are gvien n integers, and you need seperate them into k non-empty substring. After seperating,
every substring has a sum meaning the sum of all elements, and you need minimize the maximum of all sums.
*/

#include <bits/stdc++.h>

using namespace std;

bool check(long long ans, vector<int> &a, int k) {
    long long nowSum = 0;
    int block = 0;
    for (int i = 0; i < a.size(); i++) {
        nowSum += a[i];
        if (nowSum > ans) {
            block ++;
            nowSum = a[i];
        }
    }
    block++;
    return block <= k;
}

int main()
{
    int T, k, n;
    vector<int> a;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        a.resize(n);
        long long left = 0, right = 0, ans = 0, nowSum = 0;
        for (int i = 0; i < n; i++) { cin >> a[i]; right += a[i]; left = max(left, (long long)a[i]); }
        while (left <= right) {
            long long mid = (left + right) >> 1;
            if (check(mid, a, k)) {
                ans = mid;
                right = mid - 1;
            } else { left = mid + 1; }
        }
        stack<int> p;
        for (int i = n - 1; i >= 0; i--) {
            nowSum += a[i];
            if (nowSum > ans) {
                nowSum = a[i];
                k--;
                if (k > i + 1) {
                    int l = k - (i + 1);
                    k = i + 1;
                    for (; l > 0; l--) {
                        p.push(i + 1 + l); }
                }
                p.push(i + 1);
            }
        }
        for (int i = 0; i < n;i ++) {
            if (!p.empty() && i == p.top()) {
                p.pop();
                cout << "/ ";
            }
            cout << a[i] << (i == n - 1 ? "\n" : " ");
        }
    }
    return 0;
}