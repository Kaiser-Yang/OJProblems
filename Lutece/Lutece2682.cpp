#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> a;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    int minValue = std::numeric_limits<int>::max();
    for (int i = n - 1; i >= 0; i--) {
        minValue = min(minValue, a[i]);
        a[i] -= minValue;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int p;
        cin >> p;
        cout << a[p - 1] << endl;
    }

    return 0;
}