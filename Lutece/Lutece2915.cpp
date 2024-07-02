#include <bits/stdc++.h>

using namespace std;

int n, h;
long long ans;
multiset<int> hp;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h;
        hp.insert(h);
    }
    while (!hp.empty()) {
        int minHp = *hp.begin();
        hp.erase(hp.begin());
        if (hp.empty()) {
            ans += (minHp + 2) / 3;
            break;
        }
        int maxHp = *hp.rbegin();
        hp.erase(--hp.end());
        int turn = max(min(minHp, maxHp / 2), 1);
        ans += turn;
        minHp -= turn;
        maxHp -= turn * 2;
        if (minHp > 0) { hp.insert(minHp); }
        if (maxHp > 0) { hp.insert(maxHp); }
    }
    cout << ans << endl;
    return 0;
}