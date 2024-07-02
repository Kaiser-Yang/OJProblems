// problem statement: https://leetcode.cn/problems/couples-holding-hands/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
    class UFS {
        vector<int> h, siz;

    public:
        UFS(int n) {
            h.resize(n);
            siz.resize(n, 1);
            for (int i = 0; i < n; i++) { h[i] = i; }
        }
        bool isFather(int x) { return x == h[x]; }

        int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

        void join(int a, int b) {
            int fa = find(a), fb = find(b);
            if (fa == fb) { return; }
            h[fa] = fb;
            siz[fb] += siz[fa];
        }

        int size(int i) { return siz[i]; }
    };

public:
    int minSwapsCouples(vector<int> &row) {
        UFS ufs(row.size() / 2);
        for (int i = 0; i < row.size(); i += 2) { ufs.join(row[i] / 2, row[i + 1] / 2); }
        int ans = 0;
        for (int i = 0; i < row.size() / 2; i++) {
            if (ufs.isFather(i)) { ans += ufs.size(i) - 1; }
        }
        return ans;
    }
};
