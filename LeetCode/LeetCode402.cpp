// problem statement: https://leetcode.cn/problems/remove-k-digits/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        list<char> numList;
        for (auto &&ch : num) { numList.push_back(ch); }
        auto now = numList.begin(), nex = ++now;
        now--;
        bool before = false;
        while (nex != numList.end()) {
            if (k == 0) { break; }
            if (*nex >= *now) {
                before = true;
                now++;
                nex++;
                continue;
            }
            if (now == numList.begin()) { before = false; }
            k--;
            numList.erase(now);
            now = --nex;
            nex++;
            while (!before && nex != numList.end() && *nex == '0') { numList.erase(nex++); }
            if (!before) {
                now = nex;
                if (nex != numList.end()){ nex++; }
            }
        }
        while (!numList.empty() && k--) { numList.pop_back(); }
        string ans;
        for (auto &&ch : numList) { ans.push_back(ch); }
        if (ans.empty()) { ans = "0"; }
        return ans;
    }
};
