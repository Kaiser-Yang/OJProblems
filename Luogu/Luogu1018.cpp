#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 41;
constexpr int MAXK = 7;

int n, k;
string number;
string dp[MAXN][MAXK];

string add(string &a, string &b)
{
	string res;
	bool swapped = false;
	if (a.length() > b.length()) {
		swap(a, b);
		swapped = true;
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int n = a.length(), m = b.length();
	res.resize(m + 1, 0);
	for (int i = 0; i < n; i++ ) {
		res[i + 1] = (res[i] + a[i] - '0' + b[i] - '0') / 10;
		res[i] = (res[i] + a[i] - '0' + b[i] - '0') % 10;
	}
	for (int i = n; i < m; i++) {
		res[i + 1] = (res[i] + b[i] - '0') / 10;
		res[i] = (res[i] + b[i] - '0') % 10;
	}
	for (int i = 0; i < res.length(); i++) { res[i] += '0'; }
	while (res.length() > 1 && res.back() == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (swapped) { swap(a, b); }
	return res;
}

string multiply(string &a, char b)
{
	string res;
	reverse(a.begin(), a.end());
	res.resize(a.length() + 1, 0);
	for (int i = 0; i < a.length(); i++) {
		res[i + 1] = (res[i] + (a[i] - '0') * (b - '0')) / 10;
		res[i] = (res[i] + (a[i] - '0') * (b - '0')) % 10;
	}
	for (int i = 0; i < res.length(); i++) { res[i] += '0'; }
	while (res.length() > 1 && res.back() == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	reverse(a.begin(), a.end());
	return res;
}

string multiply(string &a, string &b)
{
	string res = "0";
	bool swapped = false;
	if (a.length() > b.length()) { swap(a, b); swapped = true; }
	int n = a.length(), m = b.length();
	for (int i = n - 1; i >= 0; i--) {
		string temp = multiply(b, a[i]);
		for (int j = i; j < n - 1; j++) { temp.push_back('0'); }
		res = add(res, temp);
	}
	if (swapped) { swap(a, b); }
	return res;
}

int cmp(const string &a, const string &b)
{
	if (a.length() < b.length()) {
		return -1;
	} else if (a.length() == b.length()) {
		for (int i = 0; i < a.length(); i++) {
			if (a[i] > b[i]) {
				return 1;
			} else if (a[i] < b[i]) {
				return -1;
			}
		}
		return 0;
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k >> number;
	for (int i = 0; i < n; i++) { dp[i][0] = number.substr(0, i + 1); }
	for (int kk =  1; kk <= k; kk++) {
		for (int i = kk; i < n; i++) {
			for (int j = kk - 1; j < i; j++) {
				string newNumber = number.substr(j + 1, i - j);
				string temp = multiply(dp[j][kk - 1], newNumber);
				if (cmp(dp[i][kk], temp) < 0) {
					dp[i][kk] = temp;
				}
			}
		}
	}
	cout << dp[n - 1][k] << endl;
	return 0;
}
