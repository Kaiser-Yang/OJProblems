#include <bits/stdc++.h>

using namespace std;

int n, m;
long long q;
vector<long long> a;
vector<long long> len;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n + 1);
    len.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    for (int i = 1; i <= n; i++) {
        len[i] = 1;
        while (a[i] % 3 == 0) {
            len[i] *= 3;
            a[i] /= 3;
        }
    }
    for (int i = 1; i <= n; i++) {
        len[i] += len[i - 1];
    }
    for (int i = 0; i < m; i++) {
        cin >> q;
        int pos = lower_bound(len.begin(), len.end(), q) - len.begin();
        cout << a[pos] << " ";
    }
    cout << endl;
    return 0;
}