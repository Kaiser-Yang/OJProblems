#include <bits/stdc++.h>

using namespace std;

int n;
string m;
map<char, int> number;
map<int, char> character;

string add(string &a, string &b)
{
	string res;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	res.resize(a.length() + 1, '0');
	for (int i = 0; i < a.length(); i++) {
		res[i + 1] += (number[res[i]] + number[a[i]] + number[b[i]]) / n;
		res[i] = character[(number[res[i]] + number[a[i]] + number[b[i]]) % n];
	}
	if (res[a.length()] == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	return res;
}

int main()
{
	for (int i = 0; i <= 9; i++) { number[i + '0'] = i; character[i] = '0' + i; }
	for (int i = 10; i <= 16; i++) { number[i - 10 + 'A'] = i;  character[i] = i - 10 + 'A'; }
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i <= 30; i++) {
		string temp = m;
		reverse(temp.begin(), temp.end());
		if (m == temp) {
			cout << "STEP=" << i << endl;
			return 0;
		}
		m = add(m, temp);
	}
	cout << "Impossible!\n";
	return 0;
}
