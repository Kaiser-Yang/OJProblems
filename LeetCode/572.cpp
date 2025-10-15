// problem statement: https://leetcode.cn/problems/subtree-of-another-tree/description/

#include <cassert>
#include <functional>
#include <limits>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot) {
        auto &&text = serialize(root);
        auto &&word = serialize(subRoot);
        return kmp(text, word).size() > 0;
    }

private:
    std::vector<int> serialize(TreeNode *root) {
        std::vector<int> res;
        std::function<void(TreeNode *)> dfs = [&](TreeNode *node) {
            if (node == nullptr) {
                res.emplace_back(std::numeric_limits<int>::max());
                return;
            }
            res.emplace_back(node->val);
            dfs(node->left);
            dfs(node->right);
        };
        dfs(root);
        return res;
    }

    template <typename T>
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
    template <typename T>
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
};
