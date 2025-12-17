#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<string> a;
    while (cin >> n && n != 0) {
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        sort(a.begin(), a.end());
        int midLeft = n / 2 - 1, midRight = n / 2;
        int len1 = a[midLeft].length(), len2 = a[midRight].length(), i = 0;
        while (i < len1 && i < len2 && a[midLeft][i] == a[midRight][i]) {
            cout << char(a[midLeft][i]);
            i++;
        }
        if (i == len1 - 1) {
            cout << char(a[midLeft][i]);
        } else if (i == len2 - 1 && i < len1) {
            if (a[midLeft][i] + 2 <= a[midRight][i]) {
                cout << char(a[midLeft][i] + 1);
            } else {
                cout << char(a[midLeft][i]);
                i++;
                while (i < len1 && a[midLeft][i] == 'Z') {
                    i++;
                    cout << "Z";
                }
                if (i == len1 - 1) {
                    cout << char(a[midLeft][i]);
                } else if (i < len1) {
                    cout << char(a[midLeft][i] + 1);
                }
            }
        } else if (i < len1) {
            cout << char(a[midLeft][i] + 1);
        }
        cout << endl;
    }
    return 0;
}
