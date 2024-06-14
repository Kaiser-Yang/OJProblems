// problem statement: http://poj.org/problem?id=1780
// Tag: having been in my blog

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

int len[MAXN];
int g[MAXN][10];

struct Node 
{
    int first, second;
};

Node s[MAXN * 100];

void hierholzer(int startNode, int index)
{
    int tp = 0, u = 0, w = 0, v = 0, newW = 0;
    s[tp].first = startNode;
    s[tp].second = 0;
    tp++;
    while (tp) {
        u = s[tp - 1].first, w= s[tp - 1].second;
        if (cnt[u] < len[u]) {
            v = (u * 10 + g[u][cnt[u]]) % tenPow[index];
            newW = g[u][cnt[u]];
            cnt[u]++;
            s[tp].first = v;
            s[tp].second = newW;
            tp++;
        } else {
            ans[index].push_back(s[tp - 1].second + '0');
            tp--;
        }
    }
}

int main()
{
    n = 10;
    ans[0] = "9876543210";
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            cnt[j] = 0;
            if (len[j]) { continue; }
            for (int k = 0; k < 10; k++) { g[j][len[j]++] = k; }
        }
        ans[i].reserve(tenPow[i + 1] + i);
        hierholzer(0, i);
        for (int j = 0; j < i - 1; j++) { ans[i].push_back('0'); }
        n *= 10;
    }
    while (scanf("%d", &n) && n != 0) {
        for (int i = ans[n - 1].length() - 1; i >= 0; i--) { putchar(ans[n - 1][i]); }
        putchar('\n');
    }
	return 0;
}
