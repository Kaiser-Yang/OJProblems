#include <bits/stdc++.h>

using namespace std;

constexpr int MAXM = 22;
constexpr int MAXP = 110;

int m, n, p;
string name[MAXM], sentence[MAXP];
set<string> criminor;
map<string, int> id;

string weekDay[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

bool check(const string &criminor, const string &today)
{
	vector<int> liar(m, -1);
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < p; i++) {
		stringstream ss(sentence[i]);
		string nowName;
		ss >> nowName;
		nowName.pop_back();
		int nowId = id[nowName];
		if (sentence[i].find("I am not guilty.") != sentence[i].npos) {
			if (nowName == criminor) {
				if (liar[nowId] == 0) { return false; }
                else if (liar[nowId] == -1) {
                    liar[nowId] = 1;
                    cnt2++;
                }
				liar[nowId] = 1;
			} else {
				if (liar[nowId] == 1) { return false; }
                else if (liar[nowId] == -1) {
				    liar[nowId] = 0;
                    cnt1++;
                }
			}
		} else if (sentence[i].find("I am guilty.") != sentence[i].npos) {
			if (nowName == criminor) {
				if (liar[nowId] == 1) { return false; }
                else if (liar[nowId] == -1) {
				    liar[nowId] = 0;
                    cnt1++;
                }
			} else {
				if (liar[nowId] == 0) { return false; }
                else if (liar[nowId] == -1) {
				    liar[nowId] = 1;
                    cnt2++;
                }
			}
		} else if (sentence[i].find(" is guilty.") != sentence[i].npos) {
			string who;
			ss >> who;
			if (who == criminor) {
				if (liar[nowId] == 1) { return false; }
                else if (liar[nowId] == -1) {
                    liar[nowId] = 0;
                    cnt1++;
                }
			} else {
				if (liar[nowId] == 0) { return false; }
				else if (liar[nowId] == -1) {
				    liar[nowId] = 1;
                    cnt2++;
                }
			}
		} else if (sentence[i].find(" is not guilty.") != sentence[i].npos) {
			string who;
			ss >> who;
			if (who == criminor) {
				if (liar[nowId] == 0) { return false; }
				else if (liar[nowId] == -1) {
				    liar[nowId] = 1;
                    cnt2++;
                }
			} else {
				if (liar[nowId] == 1) { return false; }
				else if (liar[nowId] == -1) {
                    liar[nowId] = 0;
                    cnt1++;
                }
			}
		} else if (sentence[i].find("Today is ") != sentence[i].npos) {
			string day;
			ss >> day >> day >> day;
			day.pop_back();
			if (day == today) {
				if (liar[nowId] == 1) { return false; }
				else if (liar[nowId] == -1) {
                    liar[nowId] = 0;
                    cnt1++;
                }
			} else {
				if (liar[nowId] == 0) { return false; }
				else if (liar[nowId] == -1) {
				    liar[nowId] = 1;
                    cnt2++;
                }
			}
		}
	}
	return cnt1 <= m-n && cnt2 <= n;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> m >> n >> p;
	for (int i = 0; i < m; i++) {
		cin >> name[i];
		id[name[i]] = i;
	}
	char ch;
	do {
		ch = cin.get();
	} while (ch != '\n');
	for (int i = 0; i < p; i++) {
		getline(cin, sentence[i]);
		while (sentence[i].back() == '\r' || sentence[i].back() == '\n') { sentence[i].pop_back(); }
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 7; j++) {
			if (check(name[i], weekDay[j])) {
				criminor.insert(name[i]);
			}
		}
	}
	if (criminor.size() > 1) {
		cout << "Cannot Determine\n";
	} else if (criminor.size() == 0) {
		cout << "Impossible\n";
	} else {
		cout << *criminor.begin() << endl;
	}
	return 0;
}
