// problem statement: https://www.luogu.com.cn/problem/P1364
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100 + 10;

int n, totPeople, ans = numeric_limits<int>::max();
int size[MAXN], depth[MAXN], dp[MAXN];

struct Node
{
    int left, right, w;
} node[MAXN];

void dfs(int u)
{
    if (node[u].left != 0) {
        depth[node[u].left] = depth[u] + 1;
        dfs(node[u].left);
    }
    if (node[u].right != 0) {
        depth[node[u].right] = depth[u] + 1;
        dfs(node[u].right);
    }
    size[u] = node[u].w + size[node[u].right] + size[node[u].left];
    dp[1] += node[u].w * depth[u]; // disance from u to 1 is depth[u].
}

void updateDp(int u, int par)
{
    // the first -size[u] means that the sub-tree u's nodes has no need
    // to trapass the path between u and par,
    // the totPeople - size[u] means that all the other nodes
    // which are node in the sub-tree u need trapass the path between u and par.
    dp[u] = dp[par] - size[u] + totPeople - size[u];
    ans = min(ans, dp[u]);
}

void treeDP(int u)
{
    if (node[u].left != 0) {
        updateDp(node[u].left, u);
        treeDP(node[u].left);
    }
    if (node[u].right != 0) {
        updateDp(node[u].right, u);
        treeDP(node[u].right);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].w >> node[i].left >> node[i].right;
        totPeople += node[i].w;
    }
    dfs(1);
    ans = dp[1];
    treeDP(1);
    cout << ans << endl;
	return 0;
}
