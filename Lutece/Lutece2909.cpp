#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> len;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    len.resize(m);
    for (int i = 0; i < m; i++) { cin >> len[i]; }
    int x = 0;
    for (int i = 0; i < m; i++) { x += len[i]; }
    x = n - x - m + 1;
    int pos = 0;
    for (int i = 0; i < m; i++) {
        int left = pos, right = pos + min(x, len[i]) - 1;
        for (int j = left; j <= right && n > 0; j++) { cout << "?"; n--;}
        left = pos + min(x, len[i]);
        right = pos + len[i] - 1;
        for (int j = left; j <= right && n > 0;j ++) { cout << "1"; n--;}
        if (n > 0 && x == 0) { cout << "0"; n--; }
        else if (n > 0 && x != 0) { cout << "?"; n--; }
        pos += len[i] + 1;
    }
    while (n--) { cout << "?"; }
    cout << endl;
    return 0;
}