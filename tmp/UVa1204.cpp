#include <bits/stdc++.h>

using namespace std;

int getCover(string s1, int iReversed, string s2, int jReversed) {
    if (iReversed) { reverse(s1.begin(), s1.end()); }
    if (jReversed) { reverse(s2.begin(), s2.end()); }
    int len1 = s1.length(), len2 = s2.length();
    for (int i = 1; i < len1; i++) {
        if (i + len2 <= len1) { continue; }
        bool ok = true;
        for (int j = 0; i + j < len1; j++) {
            if (s1[i + j] != s2[j]) {
                ok = false;
                break;
            }
        }
        if (ok) { return len1 - i; }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    string str;
    vector<string> s, temp;
    vector<vector<vector<vector<int>>>> cover;
    vector<vector<vector<int>>> dp;
    while (cin >> n && n != 0) {
        s.clear();
        temp.clear();
        for (int i = 0; i < n; i++) {
            cin >> str;
            temp.push_back(str);
        }
        sort(temp.begin(), temp.end(), [](const string &lhs, const string &rhs) {
            return lhs.length() > rhs.length();
        });
        for (int i = 0; i < n; i++) {
            bool isSub = false;
            for (int j = 0; j < i; j++) {
                if (temp[j].find(temp[i]) != string::npos) {
                    isSub = true;
                    break;
                }
            }
            if (!isSub) { s.push_back(temp[i]); }
        }
        int sumLen = 0;
        for (int i = 0; i < s.size(); i++) { sumLen += s[i].length(); }
        cover.clear();
        cover.resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            cover[i].resize(2);
            for (int iReversed = 0; iReversed < 2; iReversed++) {
                cover[i][iReversed].resize(s.size());
                for (int j = 0; j < s.size(); j++) {
                    cover[i][iReversed][j].resize(2);
                    for (int jReversed = 0; jReversed < 2; jReversed++) {
                        cover[i][iReversed][j][jReversed] =
                            getCover(s[i], iReversed, s[j], jReversed);
                    }
                }
            }
        }
        dp.clear();
        dp.resize(1 << s.size());
        for (int i = 0; i < 1 << s.size(); i++) {
            dp[i].resize(s.size());
            for (int j = 0; j < s.size(); j++) { dp[i][j].resize(2, -1); }
        }
        dp[1][0][0] = 0;
        for (int i = 1; i < 1 << s.size(); i++) {
            for (int j = 0; j < s.size(); j++) {
                if (!(i & (1 << j))) { continue; }
                for (int reversed = 0; reversed < 2; reversed++) {
                    if (dp[i][j][reversed] == -1) { continue; }
                    for (int k = 0; k < s.size(); k++) {
                        if (i & (1 << k)) { continue; }
                        for (int l = 0; l < 2; l++) {
                            dp[i | (1 << k)][k][l] =
                                max(dp[i | (1 << k)][k][l],
                                    dp[i][j][reversed] + cover[j][reversed][k][l]);
                        }
                    }
                }
            }
        }
        int ans = sumLen;
        for (int i = 0; i < s.size(); i++) {
            for (int reversed = 0; reversed < 2; reversed++) {
                if (dp[(1 << s.size()) - 1][i][reversed] != -1) {
                    ans = min(
                        ans,
                        sumLen - dp[(1 << s.size()) - 1][i][reversed] - cover[i][reversed][0][0]);
                }
            }
        }
        if (ans < 2) { ans = 2; }
        cout << ans << endl;
    }
    return 0;
}