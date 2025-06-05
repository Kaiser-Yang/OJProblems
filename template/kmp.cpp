#include <bits/stdc++.h>

using namespace std;

vector<int> get_next(const string &word, bool use_origin_next = true) {
    assert(word.length() > 0);
    vector<int> next(word.length());
    size_t i = 1, j = 0;
    while (i < word.length()) {
        if (word[i] == word[j]) {
            i++;
            j++;
            if (use_origin_next || i == word.length() || word[i] != word[j]) {
                next[i - 1] = j;
            } else {
                next[i - 1] = next[j - 1];
            }
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    return next;
}

// Return the match position, zero-indexed
vector<int> kmp(const string &text, const string &word, bool use_origin_next = true) {
    vector<int> res;
    auto &&next = get_next(word, use_origin_next);
    size_t i = 0, j = 0;
    while (i < text.length()) {
        if (text[i] == word[j]) {
            i++;
            j++;
            if (j == word.length()) {
                res.emplace_back(i - j);
                j = next[j - 1];
            }
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    return res;
}

int main() {
    string text, word;
    cin >> text >> word;
    auto &&res = kmp(text, word);
    for (auto &&item : res) { cout << item + 1 << '\n'; }
    auto &&next = get_next(word);
    for (auto &&item : next) { cout << item << ' '; }
    return 0;
}
