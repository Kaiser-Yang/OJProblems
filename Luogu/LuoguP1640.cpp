// problem statement: https://www.luogu.com.cn/problem/P1640

#include <bits/stdc++.h>

constexpr int MAXN = 1e6 + 10;

using namespace std;

using Node = pair<int, int>;

int n;
Node node[MAXN];
int match[MAXN];
bool augmented[MAXN];

bool findAugmentedPath(int leftNode)
{
    for (int rightNode = 1; rightNode <= n; rightNode++) {
        if (augmented[rightNode] || 
            (leftNode != node[rightNode].first &&
             leftNode != node[rightNode].second)) {  continue; }
        augmented[rightNode] = true;
        if (match[rightNode] == 0 || findAugmentedPath(match[rightNode])) {
            match[rightNode] = leftNode;
            return true;
        }
    }
    return false;
}

int hungrian()
{
    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(augmented, 0, sizeof(augmented));
        if (!findAugmentedPath(i)) { break; }
        else { res++; }
    }
    return res;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].first >> node[i].second;
        if (node[i].first > node[i].second) { swap(node[i].first, node[i].second); }
    }
    cout << hungrian() << endl;
	return 0;
}
