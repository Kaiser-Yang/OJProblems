// problem statement: http://poj.org/problem?id=1780

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <cstdio>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
int cnt[MAXN], tenPow[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
string ans[6];

vector<int> g[MAXN];

struct Node 
{
    int first, second;
    Node() {}
    Node(int a, int b) : first(a), second(b) {}
};

Node s[MAXN * 100];

void hierholzer(int startNode, int index)
{
    int tp = 0;
    s[tp++] = Node(startNode, 0);
    while (tp) {
        int u = s[tp - 1].first, w= s[tp - 1].second;
        if (cnt[u] < g[u].size()) {
            int v = (u * 10 + g[u][cnt[u]]) % tenPow[index];
            int newW = g[u][cnt[u]];
            cnt[u]++;
            s[tp++] = Node(v, newW);
        } else {
            ans[index].push_back(s[tp - 1].second + '0');
            tp--;
        }
    }
}

int main()
{
    n = 10;
    ans[0] = "0123456789";
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            cnt[j] = 0;
            g[j].resize(0);
            for (int k = 0; k < 10; k++) { g[j].push_back(k); }
        }
        ans[i].reserve(tenPow[i + 1] + i);
        hierholzer(0, i);
        for (int j = 0; j < i - 1; j++) { ans[i].push_back('0'); }
        reverse(ans[i].begin(), ans[i].end());
        n *= 10;
    }
    while (scanf("%d", &n) && n != 0) {
        for (int i = 0; i < ans[n - 1].length(); i++) { putchar(ans[n - 1][i]); }
        putchar('\n');
    }
	return 0;
}
