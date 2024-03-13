// problem statement: https://codeforces.com/problemset/problem/1139/E

#include <bits/stdc++.h>

constexpr int MAXN = 5e3 + 10;
constexpr int MAXM = 5e3 + 10;
constexpr int MAXD = 5e3 + 10;

using namespace std;

int n, m, d;
int p[MAXN], c[MAXN], leave[MAXD], match[MAXM];
bool augmented[MAXM];
unordered_set<int> gone;
vector<int> ans, g[MAXM];

bool findAugmentedPath(int leftNode)
{
    for (const int &rightNode : g[leftNode]) {
        if (augmented[rightNode]) { continue; }
        augmented[rightNode] = true;
        if (match[rightNode] == -1 || findAugmentedPath(match[rightNode])) {
            match[rightNode] = leftNode;
            return true;
        }
    }
    return false;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(match, 0xff, sizeof(match));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> p[i]; }
    for (int i = 1; i <= n; i++) { cin >> c[i]; }
    cin >> d;
    for (int i = 1; i <= d; i++) {
        cin >> leave[i];
        gone.insert(leave[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (gone.count(i) == 1) { continue; }
        g[p[i]].push_back(c[i]);
    }
    int nowAns = 0;
    for (int i = d; i >= 1; i--) {
        for (int leftNode = nowAns; leftNode <= m; leftNode++) {
            memset(augmented, 0, sizeof(augmented));
            if (findAugmentedPath(leftNode)) { continue; }
            nowAns = leftNode;
            ans.push_back(nowAns);
            break;
        }
        g[p[leave[i]]].push_back(c[leave[i]]);
    }
    for (auto it = ans.rbegin(); it != ans.rend(); it++) { cout << *it << "\n"; }
	return 0;
}
