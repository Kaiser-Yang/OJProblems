// problem statement:

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> cnt;
        int num = 0;
        for (char ch : s) {
            cnt[ch]++;
            num = max(num, cnt[ch]);
        }
        if (s.length() - num < num - 1) { return ""; }
        map<int, vector<char>> id;
        for (auto item : cnt) { id[item.second].push_back(item.first); }
        list<char> ans;
        auto pos = ans.begin();
        for (auto iter = id.rbegin(); iter != id.rend(); iter++) {
            while (!iter->second.empty()) {
                if (ans.empty()) {
                    for (int i = 0; i < iter->first; i++) {
                        ans.push_back(iter->second.back());
                    }
                    pos = ++ans.begin();
                } else {
                    for (int i = 0; i < iter->first; i++) {
                        if (pos == ans.end()) {
                            ans.insert(pos, iter->second.back());
                            pos = ans.begin();
                        } else {
                            ans.insert(pos++, iter->second.back());
                        }
                    }
                }
                // cout << string(ans.begin(), ans.end()) << endl;
                iter->second.pop_back();
            }
        }
        return string(ans.begin(), ans.end());
    }
};
