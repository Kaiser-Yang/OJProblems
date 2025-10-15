#include <cassert>
#include <vector>

template<typename T>
std::vector<int> get_next(const T &word) {
    assert(word.size() > 0);
    std::vector<int> next(word.size() + 1);
    next[0] = -1;
    next[1] = 0;
    int i = 1, j = 0;
    while (i < word.size()) {
        if (word[i] == word[j]) {
            i++;
            j++;
            next[i] = j;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j];
        }
    }
    return next;
}

// Return the match position, zero-indexed
template<typename T>
std::vector<int> kmp(const T &text, const T &word) {
    std::vector<int> res;
    auto &&next = get_next(word);
    int i = 0, j = 0;
    while (i < text.size()) {
        if (text[i] == word[j]) {
            i++;
            j++;
            if (j == word.size()) {
                res.emplace_back(i - j);
                j = next[j];
            }
        } else if (j == 0) {
            i++;
        } else {
            j = next[j];
        }
    }
    return res;
}
