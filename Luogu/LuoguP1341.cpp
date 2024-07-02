// problem statement: https://www.luogu.com.cn/problem/P1341

#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_NODE_NUM = 52;

int n;
string s, ans;
int degree[MAX_NODE_NUM];
bool connected[MAX_NODE_NUM][MAX_NODE_NUM], vis[MAX_NODE_NUM];

int getId(char ch) {
    if (ch >= 'a' && ch <= 'z') { return ch - 'a' + 26; }
    return ch - 'A';
}

char getChar(int id) {
    if (id >= 0 && id <= 25) { return char(id + 'A'); }
    return char(id - 26 + 'a');
}

void dfs(int u) {
    vis[u] = true;
    for (int v = 0; v < MAX_NODE_NUM; v++) {
        if (!connected[u][v] || vis[v]) { continue; }
        dfs(v);
    }
}

void getAns(int u) {
    for (int v = 0; v < MAX_NODE_NUM; v++) {
        if (!connected[u][v]) { continue; }
        connected[u][v] = connected[v][u] = false;
        getAns(v);
    }
    ans[n--] = getChar(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int u = getId(s[0]), v = getId(s[1]);
        connected[u][v] = connected[v][u] = true;
        degree[u]++;
        degree[v]++;
    }
    int cnt = 0;
    for (int i = 0; i < MAX_NODE_NUM; i++) {
        if (!vis[i] && degree[i] != 0) {
            dfs(i);
            cnt++;
        }
    }
    if (cnt != 1) {
        cout << "No Solution" << endl;
    } else {
        cnt = 0;
        for (int i = 0; i < MAX_NODE_NUM; i++) {
            if (degree[i] & 1) { cnt++; }
        }
        if (cnt != 0 && cnt != 2) {
            cout << "No Solution" << endl;
        } else {
            ans.resize(n + 1);
            for (int i = 0; i < MAX_NODE_NUM; i++) {
                if (cnt == 0 && degree[i] != 0) {
                    getAns(i);
                    break;
                }
                if (cnt == 2 && degree[i] % 2 == 1) {
                    getAns(i);
                    break;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}