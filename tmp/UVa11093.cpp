#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> p, c;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n;
        p.resize(2 * n + 1);
        c.resize(2 * n + 1);
        for (int i = 1; i <= n; i++) { cin >> p[i]; }
        for (int i = 1; i <= n; i++) { cin >> c[i]; }
        for (int i = n + 1; i <= 2 * n; i++) {
            p[i] = p[i - n];
            c[i] = c[i - n];
        }
        cout << "Case " << t << ": ";
        for (int i = 1;;) {
            if (i > n) {
                cout << "Not possible" << endl;
                break;
            }
            bool done = true;
            int resPetrol = p[i];
            for (int j = 0; j < n; j++) {
                if (resPetrol < c[i + j]) {
                    i = i + j + 1;
                    done = false;
                    break;
                }
                resPetrol -= c[i + j];
                resPetrol += p[i + j + 1];
            }
            if (done) {
                cout << "Possible from station " << i << endl;
                break;
            }
        }
    }
    return 0;
}
