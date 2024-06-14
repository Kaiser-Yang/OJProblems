// problem statement: https://www.luogu.com.cn/problem/P1127
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;

int n, scc, startNode = numeric_limits<int>::max();
int inDegree[26], outDegree[26], cnt[26];
bool vis[26];
string word[MAXN];

stack<int> ans;

vector<int> g[26], mp[26];

void dfs(int u)
{
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) { continue; }
        dfs(v);
    }
}

void hierholzer(int u, int wordIndex)
{
    for (int &i = cnt[u]; i < mp[u].size(); ) {
        int temp = mp[u][i];
        i++;
        hierholzer(word[temp].back() - 'a', temp);
    }
    ans.push(wordIndex);
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> word[i]; }
    sort(word, word + n);
    for (int i = 0; i < n; i++) {
        int u = word[i].front() - 'a', v = word[i].back() - 'a';
        mp[u].push_back(i);
        inDegree[v]++;
        outDegree[u]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < 26; i++) {
        if (vis[i] || g[i].size() == 0) { continue; }
        dfs(i);
        scc++;
    }
    if (scc > 1) {
        cout << "***\n";
        return 0;
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 26; i++) {
        if (inDegree[i] < outDegree[i]) {
            if (inDegree[i] + 1 != outDegree[i]) {
                cout << "***\n";
                return 0;
            }
            cnt1++;
            startNode = i;
        } else if (inDegree[i] > outDegree[i]) {
            if (outDegree[i] + 1 != inDegree[i]) {
                cout << "***\n";
                return 0;
            }
            cnt2++;
        }
    }
    if (cnt1 > 1 || cnt2 > 1 || cnt1 != cnt2) {
        cout << "***\n";
        return 0;
    }
    if (cnt1 == 0) {
        for (int i = 0; i < 26; i++) {
            if (g[i].size() != 0) {
                startNode = i;
                break;
            }
        }
    }
    if (startNode == numeric_limits<int>::max()) { startNode = 0; }
    hierholzer(startNode, -1);
    ans.pop();
    while (!ans.empty()) {
        cout << word[ans.top()] << (ans.size() == 1 ? "\n" : ".");
        ans.pop();
    }
	return 0;
}
