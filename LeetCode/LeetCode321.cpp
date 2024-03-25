// problem statement: https://leetcode.cn/problems/create-maximum-number/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    void selectKSequence(vector<int>& num, int k, vector<int>& res)
    {
        int n = num.size();
        for (int i = 0; i < n; i++) {
            while (!res.empty() && res.back() < num[i] && res.size() - 1 + n - i >= k) { res.pop_back(); }
            if (res.size() < k) { res.push_back(num[i]); }
        }
        assert(res.size() == k);
    }

    bool less(const vector<int> &a, const vector<int> &b)
    {
        if (a.empty()) { return true; }
        assert(a.size() == b.size());
        int n = a.size();
        for (int i = 0; i < n; i++) {
            if (a[i] < b[i]) { return true; }
            else if (a[i] == b[i]) { continue; }
            else { return false; }
        }
        return false;
    }

    void merge(vector<int>& a, vector<int>& b, vector<int>& res)
    {
        int n = a.size(), m = b.size(), i = 0, j = 0;
        while (i < n || j < m) {
            if (i >= n || (j < m && a[i] < b[j])) { res.push_back(b[j++]); }
            else if (j >= m || (i < n && a[i] > b[j])) {res.push_back(a[i++]); }
            else {
                bool done = false;
                for (int k = 0; i + k < n || j + k < m; k++) {
                    if (a[i + k % (n - i)] == b[j + k % (m - j)]) { continue; }
                    else if (a[i + k % (n - i)] > b[j + k % (m - j)]) {
                        done = true;
                        res.push_back(a[i++]);
                        break;
                    } else {
                        done = true;
                        res.push_back(b[j++]);
                        break;
                    }
                }
                // the left part of a and the left part of b are the same.
                if (!done) { res.push_back(a[i++]); }
            }
        }
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        vector<int> res1(k), res2(k), temp(k);
        vector<int> ans;
        for (int k1 = 0; k1 <= min(k, n); k1++) {
            int k2 = min(m, k - k1);
            if (k1 + k2 != k) { continue; }
            res1.resize(0);
            res2.resize(0);
            temp.resize(0);
            selectKSequence(nums1, k1, res1);
            selectKSequence(nums2, k2, res2);
            merge(res1, res2, temp);
            if (less(ans, temp)) { ans = temp; }
        }
        return ans;
    }
};