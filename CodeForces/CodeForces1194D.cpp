#include <bits/stdc++.h>

using namespace std;

int T, n, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        if (k > n) {
            if (n % 3 == 0) {
                cout << "Bob\n";
            } else {
                cout << "Alice\n";
            }
        } else if (k == n) {
            cout << "Alice\n";
        } else {
            if (k % 3 == 0) {
                if (n % (k + 1) % 3 == 0 && n % (k + 1) != k) {
                    cout << "Bob\n";
                } else {
                    cout << "Alice\n";
                }
            } else {
                if (n % 3 == 0) {
                    cout << "Bob\n";
                } else {
                    cout << "Alice\n";
                }
            }
        }
    }
    return 0;
}
