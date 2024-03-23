// problem statement: https://www.luogu.com.cn/problem/P1209

#include <bits/stdc++.h>

constexpr int MAXM = 50 + 5;
constexpr int MAXC = 200 + 10;
constexpr int MAXS = 200 + 10;

using namespace std;

int m, c, s, cnt, ans;
int p[MAXC];
list<pair<int, int>> section;

int main()
{
	ios::sync_with_stdio(false);
    cin >> m >> s >> c;
    for (int i = 1; i <= c; i++) { cin >> p[i]; }
    sort(p + 1, p + 1 + c);
    for (int i = 1; i <= c; ) {
        int j = i;
        while (j + 1 <= c && p[j + 1] == p[j] + 1) { j++; }
        section.push_back({p[i], p[j]});
        i = j + 1;
    }
    cnt = section.size();
    for (int i = 0; i < cnt - m; i++) {
        int temp = -1;
        auto pos = section.end();
        for (auto it = section.begin(); it != section.end(); it++) {
            auto nex = ++it;
            --it;
            if (nex == section.end()) { break; }
            if (temp == - 1 || nex->first - it->second < temp) {
                temp = nex->first - it->second;
                pos = it;
                
            }
        }
        auto nex = ++pos, nexNex = ++pos;
        --pos;
        --pos;
        pair<int, int> newSection = {pos->first, nex->second};
        section.erase(pos);
        section.erase(nex);
        section.insert(nexNex, newSection);
    }
    for (auto item : section) { ans += item.second - item.first + 1; }
    cout << ans << "\n";
	return 0;
}
