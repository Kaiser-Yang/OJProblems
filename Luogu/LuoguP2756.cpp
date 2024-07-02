// problem statement: https://www.luogu.com.cn/problem/P2756

#include <bits/stdc++.h>

constexpr int MAXN = 100 + 10;
constexpr int MAXM = 100 + 10;

using namespace std;

int n, m, u, v;
int match[MAXN];
bool connected[MAXN][MAXN], augmented[MAXN];

bool findAugmentedPath(int leftNode) {
    for (int rightNode = m + 1; rightNode <= n; rightNode++) {
        if (!connected[leftNode][rightNode] || augmented[rightNode]) { continue; }
        augmented[rightNode] = true;
        if (match[rightNode] == 0 || findAugmentedPath(match[rightNode])) {
            match[rightNode] = leftNode;
            return true;
        }
    }
    return false;
}

int hungrian() {
    int res = 0;
    for (int leftNode = 1; leftNode <= m; leftNode++) {
        memset(augmented, 0, sizeof(augmented));
        res += findAugmentedPath(leftNode);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;
    while (cin >> u >> v) {
        if (u == -1 && v == -1) { break; }
        connected[u][v] = true;
    }
    cout << hungrian() << "\n";
    for (int rightNode = m = 1; rightNode <= n; rightNode++) {
        if (match[rightNode] == 0) { continue; }
        cout << match[rightNode] << " " << rightNode << "\n";
    }
    return 0;
}
