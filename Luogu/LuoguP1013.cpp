// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 10;

int n;
string s[MAXN][MAXN];
map<string, int> num;
map<int, bool> occur;

bool check(int i, int j)
{
    int res1 = num[s[i][0]] + num[s[0][j]];
    int res2 = 0;
    if (s[i][j].length() == 2) {
        res2 = num[s[i][j].substr(0, 1)] * (n - 1) + num[s[i][j].substr(1, 1)];
    } else {
        res2 = num[s[i][j]];
    }
    return res1 == res2;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> s[i][j];
        }
    }
    for (int i = 1; i < n; i++) {
        int cnt = 0;
        for (int j = 1; j < n; j++) {
            if (s[i][j].length() == 2) { cnt++; }
            else if (s[i][j].length() > 2) {
                cout << "ERROR!\n";
                return 0;
            }
        }
        num[s[i][0]] = cnt;
        if (occur.count(cnt)) {
            cout << "ERROR!\n";
            return 0;
        }
        occur[cnt] = true;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (!check(i, j)) {
                cout << "ERROR!\n";
                return 0;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        cout << s[i][0] << "=" << num[s[i][0]] << " ";
    }
    cout << endl << n - 1 << endl;
	return 0;
}
