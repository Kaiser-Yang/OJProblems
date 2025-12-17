#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n, d;
    string num;
    while (cin >> n >> d && n != 0 && d != 0) {
        cin >> num;
        vector<char> ans;
        ans.push_back(num[0]);
        for (int i = 1; i < n; i++) {
            while (d != 0 && !ans.empty() && ans.back() < num[i]) {
                d--;
                ans.pop_back();
            }
            ans.push_back(num[i]);
        }
        while (d != 0) {
            d--;
            ans.pop_back();
        }
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
