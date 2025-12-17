/*
    You are given n integers. You need check if it is non-boring.
If a sequence is non-boring, if and only if for any subsequence,
there is at least one number which only appears one time in the subsequence.
*/
#include <bits/stdc++.h>

using namespace std;

bool isNonBoring(int left, int right, vector<int> &l, vector<int> &r)
{
    if (right - left <= 1) { return true; }
    for (int i = 0; left + i <= right - 1 - i; i++) {
        if (l[left + i] < left && r[left + i] >= right) {
            return isNonBoring(left, left + i, l, r) && isNonBoring(left + i + 1, right, l, r);
        }
        if (l[right - 1 - i] < left && r[right - 1 - i] >= right) {
            return isNonBoring(left, right - 1 - i, l, r) && isNonBoring(right - i, right, l, r);
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> a, l, r;
    map<int, int> pos;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        l.clear();
        l.resize(n, -1);
        r.clear();
        r.resize(n, n);
        pos.clear();
        for (int i = 0; i < n; i++) { pos[a[i]] = -1; }
        int right = 0;
        while (right < n) {
            while (right < n && pos[a[right]] == -1) {
                pos[a[right]] = right;
                right++;
            }
            if (right < n) {
                l[right] = pos[a[right]];
                r[pos[a[right]]] = right;
            }
            pos[a[right]] = right;
            right++;
        }
        cout << (isNonBoring(0, n, l, r) ? "non-boring" : "boring") << endl;
    }
    return 0;
}
