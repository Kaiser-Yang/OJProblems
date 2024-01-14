#include <bits/stdc++.h>

using namespace std;

string s, t;

void getNext(const string &s, vector<int> &next)
{
    int n = s.length();
    next[0] = -1;
    int j = -1;
    for (int i = 1; i < n; i++) {
        while (j != -1 && s[i] != s[j + 1]) { j = next[j]; }
        if (s[j + 1] == s[i]) { j++; }
        next[i] = j;
    }
}

void KMP(const string &s, const string &t)
{
    int res = 0;
    int n = s.length(), m = t.length();
    vector<int> next(m);
    getNext(t, next);
    int j = -1;
    for (int i = 0; i < n; i++) {
        while (j != -1 && s[i] != t[j + 1]) { j = next[j]; }
        if (t[j + 1] == s[i]) { j++; }
        if (j == m - 1) {
            res++;
            j = next[j];
        }
    }
    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> s >> t;
    KMP(s, t);
    return 0;
}