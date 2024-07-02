// problem statement: https://www.luogu.com.cn/problem/P3805

#include <bits/stdc++.h>

constexpr size_t MAXN = 1.1e7;

using namespace std;

string str;

size_t manacher(const string &src) {
    string s;
    s.push_back('#');
    for (auto &&ch : src) {
        s.push_back(ch);
        s.push_back('#');
    }
    s.push_back('#');
    size_t ans = 0;
    vector<size_t> p(s.size());
    p[0] = 1;
    size_t id = 0, max_right = 0;
    for (size_t i = 1; i < s.length(); i++) {
        if (i < max_right) {
            p[i] = min(p[2 * id - i], max_right - i + 1);
        } else {
            p[i] = 1;
        }
        while (i + p[i] < s.length() && i >= p[i] && s[i + p[i]] == s[i - p[i]]) {
            p[i]++;
        }
        if (i + p[i] - 1 > max_right) {
            max_right = i + p[i] - 1;
            id = i;
        }
        ans = max(ans, p[i] - 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    cout << manacher(str) << '\n';
    return 0;
}
