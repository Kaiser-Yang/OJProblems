// problem state: https://www.luogu.com.cn/problem/P3386

#include <bits/stdc++.h>

const int MAXN = 1010;
const int MAXM = 1010;

using namespace std;

int n, m, e, u, v;
int match[MAXM];
bool connected[MAXN][MAXM], augmented[MAXM];

bool findAugmentedPath(int leftnode) {
    for (int rightNode = 1; rightNode <= m; rightNode++) {
        if (augmented[rightNode] || !connected[leftnode][rightNode]) { continue; }
        augmented[rightNode] = true;
        if (match[rightNode] == 0 || findAugmentedPath(match[rightNode])) {
            match[rightNode] = leftnode;
            return true;
        }
    }
    return false;
}

int hungrian() {
    int res = 0;
    for (int leftNode = 1; leftNode <= n; leftNode++) {
        memset(augmented, 0, sizeof(augmented));
        res += findAugmentedPath(leftNode);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> e;
    for (int i = 1; i <= e; i++) {
        cin >> u >> v;
        if (u > n || v > m) { continue; }
        connected[u][v] = true;
    }
    cout << hungrian() << "\n";
    return 0;
}