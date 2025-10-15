// problem statement: https://leetcode.cn/problems/linked-list-in-binary-tree/description/

#include <cassert>
#include <functional>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    bool isSubPath(ListNode *head, TreeNode *root) {
        std::vector<int> a;
        for (auto p = head; p != nullptr; p = p->next) { a.push_back(p->val); }
        auto &&next = get_next(a);
        std::function<bool(TreeNode *, int)> dfs = [&](TreeNode *node, int j) {
            if (node == nullptr) { return false; }
            while (j >= 0 && node->val != a[j]) { j = next[j]; }
            j++;
            if (j == a.size()) { return true; }
            return dfs(node->left, j) || dfs(node->right, j);
        };
        return dfs(root, 0);
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
};
