#include <bits/stdc++.h>

using namespace std;

void mergeSort(vector<int> &a, int l, int r, vector<int> &t, int &cnt) {
    if (r - l <= 1) { return; }
    int mid = (l + r) >> 1;
    mergeSort(a, l, mid, t, cnt);
    mergeSort(a, mid, r, t, cnt);
    int i = l, j = mid, k = l;
    while (i < mid || j < r) {
        if (j >= r || (i < mid && a[i] <= a[j])) {
            t[k++] = a[i++];
        } else {
            t[k++] = a[j++];
            cnt += mid - i;
        }
    }
    for (int i = l; i < r; i++) { a[i] = t[i]; }
}

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> a;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        vector<int> t;
        t.resize(n);
        int cnt = 0;
        mergeSort(a, 0, n, t, cnt);
        if (cnt % 2 == 1 && n % 2 == 1) {
            cout << "impossible" << endl;
        } else {
            cout << "possible" << endl;
        }
    }
    return 0;
}
