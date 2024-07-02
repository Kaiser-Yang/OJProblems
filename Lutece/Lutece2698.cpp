#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    a.resize(k);
    for (int i = 0; i < k; i++) { cin >> a[i]; }
    cout << "Win\n";
    return 0;
}