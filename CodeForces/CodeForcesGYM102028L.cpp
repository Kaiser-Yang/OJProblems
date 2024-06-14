// problem statement: https://codeforces.com/gym/102028/problem/L
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;
constexpr int MOD  = 1e9 + 7;

int T, n, m, u, v, ecnt, newEcnt, newEcnt1;
int cnt1[MAXN], cnt2[MAXN], head[MAXN], newHead[MAXN], newHead1[MAXN], degree[MAXN];
bool vis[MAXN];
long long cnt;
long long ans[5];

struct Graph
{
    int to, nex;
} g[MAXM << 1], newG[MAXM], newG1[MAXM];

void addEdge(int u, int v, Graph *es, int &ecnt, int *head)
{
    es[ecnt].to = v;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

constexpr long long quickPow(long long a, long long b, long long MOD)
{
    long long res = 1 % MOD;
    while (b > 0) {
        if (b & 1) { res = res * a % MOD; }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

constexpr int POWER2 = quickPow(2, MOD - 2, MOD);
constexpr int POWER24 = quickPow(24, MOD - 2, MOD);

// One centroid with four nodes.
long long solve0()
{
    ans[0] = 0;
    for (int u = 1; u <= n; u++) {
        if (degree[u] < 4) { continue; }
        long long temp = 1;
        for (int j = 0; j < 4; j++) { temp = temp * (degree[u] - j) % MOD; }
        temp = temp * POWER24 % MOD;
        ans[0] = (ans[0] + temp) % MOD;
    }
    return ans[0];
}

// Four nodes circle
long long solve1()
{
    ans[1] = 0;
    for (int a = 1; a <= n; a++) {
        for (int i = newHead[a]; i != -1; i = newG[i].nex) {
            int b = newG[i].to;
            for (int j = newHead[b]; j != -1; j = newG[j].nex) {
                int c = newG[j].to;
                cnt1[c]++;
            }
        }
        for (int i = newHead1[a]; i != -1; i = newG1[i].nex) {
            int b = newG1[i].to;
            for (int j = newHead[b]; j != -1; j = newG[j].nex) {
                int c = newG[j].to;
                if (c == a) { continue; }
                cnt2[c]++;
            }
        }
        for (int i = newHead[a]; i != -1; i = newG[i].nex) {
            int b = newG[i].to;
            for (int j = newHead[b]; j != -1; j = newG[j].nex) {
                int c = newG[j].to;
                ans[1] = (ans[1] + 1LL * cnt1[c] * (cnt1[c] - 1) / 2 % MOD + 1LL * cnt1[c] * cnt2[c] % MOD) % MOD;
                cnt1[c] = 0;
            }
        }
        for (int i = newHead1[a]; i != -1; i = newG1[i].nex) {
            int b = newG1[i].to;
            for (int j = newHead[b]; j != -1; j = newG[j].nex) {
                int c = newG[j].to;
                if (c == a) { continue; }
                ans[1] = (ans[1] + (1LL * cnt2[c] * (cnt2[c] - 1) / 2) % MOD * POWER2 % MOD) % MOD;
                cnt2[c] = 0;
            }
        }
    }
    return ans[1];
}

// Three nodes circle with one more node.
long long solve2()
{
    ans[2] = cnt = 0;
    for (int a = 1; a <= n; a++) {
        for (int i = newHead[a]; i != -1; i = newG[i].nex) {
            int b = newG[i].to;
            vis[b] = true; 
        }
        for (int i = newHead[a]; i != -1; i = newG[i].nex) {
            int b = newG[i].to;
            for (int j = newHead[b]; j != -1; j = newG[j].nex) {
                int c = newG[j].to;
                if (!vis[c]) { continue; }
                cnt = (cnt + 1) % MOD;
                ans[2] = (ans[2] + degree[a] + degree[b] + degree[c] - 6) % MOD;
            }
        }
        for (int i = newHead[a]; i != -1; i = newG[i].nex) {
            int b = newG[i].to;
            vis[b] = false; 
        }
    }
    return ans[2];
}

// Four nodes line with one node connected with its centroid
long long solve3()
{
    ans[3] = 0;
    for (int a = 1; a <= n; a++) {
        for (int i = head[a]; i != -1; i = g[i].nex) {
            int b = g[i].to;
            ans[3] = (ans[3] + 1LL * (degree[a] - 1) * (degree[b] - 1) * (degree[b] - 2) / 2 % MOD) % MOD;
        }
    }
    ans[3] = ans[3] - 2 * ans[2] % MOD;
    return ans[3] = (ans[3] % MOD + MOD) % MOD;
}

// Five nodes line
long long solve4()
{
    ans[4] = 0;
    for (int a = 1; a <= n; a++) {
        long long temp = 0;
        for (int i = head[a]; i != -1; i = g[i].nex) {
            int b = g[i].to;
            ans[4] = (ans[4] + temp * (degree[b] - 1) % MOD) % MOD;
            temp = (temp + degree[b] - 1) % MOD;
        }
    }
    ans[4] = (ans[4] - 2 * ans[2] - 4 * ans[1] - 3 * cnt);
    return ans[4] = (ans[4] % MOD + MOD) % MOD;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        ecnt = newEcnt = newEcnt1 = 0;
        memset(head, 0xff, sizeof(int) * (n + 1));
        memset(newHead, 0xff, sizeof(int) * (n + 1));
        memset(newHead1, 0xff, sizeof(int) * (n + 1));
        memset(degree + 1, 0x00, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            addEdge(u, v, g, ecnt, head);
            addEdge(v, u, g, ecnt, head);
            degree[u]++;
            degree[v]++;
        }
        for (int a = 1; a <= n; a++) {
            for (int i = head[a]; i != -1; i = g[i].nex) {
                int b = g[i].to;
                if (degree[a] < degree[b] || (degree[a] == degree[b] && a < b)) { addEdge(a, b, newG, newEcnt, newHead); }
                else { addEdge(a, b, newG1, newEcnt1, newHead1); }
            }
        }
        cout << (solve0() + solve1() + solve2() + solve3() + solve4()) % MOD << endl;
    }
	return 0;
}
