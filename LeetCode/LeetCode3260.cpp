// problem statement: https://leetcode.cn/problems/find-the-largest-palindrome-divisible-by-k/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string largestPalindrome(int n, int k) {
        if (k == 1 || k == 3 || k == 9) { 
            return string(n, '9');
        } else if (k == 2) {
            if (n <= 2) { return string(n, '8'); }
            return "8" + string(n - 2, '9') + "8";
        } else if (k == 4) {
            if (n <= 4) { return string(n, '8'); }
            return "88" + string(n - 4, '9') + "88";
        } else if (k == 5) {
            if (n <= 2) { return string(n, '5'); }
            return "5" + string(n - 2, '9') + "5";
        } else if (k == 6) {
            if (n <= 2) { return string(n, '6'); }
            if (n % 2 == 1) { return "8" + string((n - 3) / 2, '9') + "8" + string((n - 3) / 2, '9') + "8"; }
            return "8" + string((n - 4) / 2, '9') + "77" + string((n - 4) / 2, '9') + "8";
        } else if (k == 7) {
            if (n % 6 == 0) { return string(n, '9'); }
            vector<string> middle = {"4", "44", "6", "44", "4"};
            if (n / 6 % 2 == 0) {
                middle = {"7", "77", "5", "77", "7"};
            }
            int m = middle[n % 6 - 1].length();
            return string((n - m) / 2, '9') + middle[n % 6 - 1] + string((n - m) / 2, '9');
        } else if (k == 8) {
            if (n <= 6) { return string(n, '8'); }
            return "888" + string(n - 6, '9') + "888";
        }
        return "";
    }
};
