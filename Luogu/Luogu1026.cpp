#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 200 + 10;
constexpr int MAXK = 40 + 10;

int n, k, s;
string str, temp;
vector<string> dictionary;
set<int> matchPos;
int num[MAXN][MAXN];
int dp[MAXN][MAXK];

void getNext(const string &s, vector<int> &nex)
{
	int n = s.length();
	nex.clear();
	nex.resize(n, -1);
	nex[0] = -1;
	int i = 1, j = -1;
	for (int i = 1; i < n; i++) {
		while (j != -1 && s[i] != s[j + 1]) { j = nex[j]; }
		if (s[i] == s[j + 1]) { j++; }
		nex[i] = j;
	}
}

void KMP(const string &s, const string &t)
{
	vector<int> nex;
	getNext(t, nex);
	int len1 = s.length(), len2 = t.length();
	int j = -1;
	for (int i = 0; i < len1; i++) {
		while (j != -1 && s[i] != t[j + 1]) { j = nex[j]; }
		if (s[i] == t[j + 1]) { j++; }
		if (j == len2 - 1) {
			matchPos.insert(i - len2 + 1);
			j = nex[j];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		str += temp;
	}
	n *= 20;
	cin >> s;
	for (int i = 0; i < s; i++) {
		cin >> temp;
		dictionary.push_back(temp);
	}
	for (int l = 0; l < n; l++) {
		for (int r = l; r < n; r++) {
			matchPos.clear();
			temp = str.substr(l, r - l + 1);
			for (int i = 0; i < s; i++) {
				KMP(temp, dictionary[i]);
			}
			num[l][r] = matchPos.size();
		}
	}
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++) {
		dp[i][1] = num[0][i];
		for (int kk = 2; kk <= min(i + 1, k); kk++) {
			for (int j = kk - 2; j < i; j++) {
				dp[i][kk] = max(dp[i][kk], dp[j][kk - 1] + num[j + 1][i]);
			}
		}
	}
	cout << dp[n - 1][k] << endl;
	return 0;
}