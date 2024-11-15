// problem statement: https://www.luogu.com.cn/problem/P3375

#include <bits/stdc++.h>

using namespace std;

string text, pattern;
vector<int> border;

void pre_kmp(const string &pattern, vector<int> &border) {
    size_t n = pattern.length();
    border.resize(n);
    border[0] = -1;
    int j = -1;
    for (size_t i = 1; i < n; i++) {
        while (j >= 0 && pattern[i] != pattern[j + 1]) { j = border[j]; }
        if (pattern[i] == pattern[j + 1]) { j++; }
        border[i] = j;
    }
}

void kmp(const string &text, const string &pattern, vector<int> &border) {
    pre_kmp(pattern, border);
    size_t n = text.length(), m = pattern.length();
    int j = -1;
    for (size_t i = 0; i < n; i++) {
        while (j >= 0 && text[i] != pattern[j + 1]) { j = border[j]; }
        if (text[i] == pattern[j + 1]) { j++; }
        if (j + 1 == m) {
            cout << i + 1 - m + 1 << '\n';
            j = border[j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> text >> pattern;
    kmp(text, pattern, border);
    for (size_t i = 0; i < border.size(); i++) {
        cout << border[i] + 1 << (i == border.size() - 1 ? "\n" : " ");
    }
    return 0;
}
