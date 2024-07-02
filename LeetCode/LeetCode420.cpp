// problem statement: https://leetcode.cn/problems/strong-password-checker/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int getID(char ch) {
        if (ch >= 'a' && ch <= 'z') { return 0; }
        if (ch >= 'A' && ch <= 'Z') { return 1; }
        if (ch >= '0' && ch <= '9') { return 2; }
        return 3;
    }

public:
    int strongPasswordChecker(string password) {
        int n = password.length(), deleteNum = max(0, n - 20), ans = deleteNum;
        vector<bool> deleted(n);
        while (deleteNum > 0) {
            int p[3] = {-1, -1, -1}, i = 0, j = 0;
            while (i < n) {
                if (deleted[i]) {
                    i++;
                    continue;
                }
                int j = i + 1;
                while (j < n && password[j] == password[i]) { j++; }
                if (j - i >= 3) { p[(j - i) % 3] = i; }
                i = j;
            }
            if (p[0] != -1) {
                deleteNum--;
                deleted[p[0]] = true;
            } else if (p[1] != -1) {
                deleteNum--;
                deleted[p[1]] = true;
                if (deleteNum > 0) {
                    deleteNum--;
                    deleted[p[1] + 1] = true;
                }
            } else if (p[2] != -1) {
                deleteNum--;
                deleted[p[2]] = true;
                if (deleteNum > 0) {
                    deleteNum--;
                    deleted[p[2] + 1] = true;
                }
                if (deleteNum > 0) {
                    deleteNum--;
                    deleted[p[2] + 2] = true;
                }
            } else {
                break;
            }
        }
        int cnt[4] = {0, 0, 0, n};
        for (int i = 0; i < n; i++) {
            if (deleted[i]) { continue; }
            cnt[getID(password[i])]++;
        }
        for (int i = 0; i < n; i++) {
            if (deleted[i] || cnt[getID(password[i])] <= 1) { continue; }
            if (deleteNum == 0) { break; }
            deleteNum--;
            cnt[getID(password[i])]--;
            deleted[i] = true;
        }
        int cnt1 = 0;
        int i = 0, j = 0;
        while (i < n) {
            if (deleted[i]) {
                i++;
                continue;
            }
            j = i + 1;
            while (j < n && !deleted[j] && password[j] == password[i]) { j++; }
            cnt1 += (j - i) / 3;
            i = j;
        }
        int cnt2 = count_if(cnt, cnt + 3, [](int val) { return val > 0; });
        n        = count_if(deleted.begin(), deleted.end(), [](bool item) { return !item; });
        if (n >= 6 && n <= 20) { return ans + max(cnt1, 3 - cnt2); }
        if (n <= 5) { return 6 - n + max(0, 3 - cnt2 - (6 - n)); }
        return -1;
    }
};
