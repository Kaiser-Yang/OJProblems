// problem statement: https://leetcode.cn/problems/path-sum-iii/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int count(TreeNode* root, long long targetSum) {
        if (root == nullptr) { return 0; }
        return (root->val == targetSum) + 
               count(root->left, (long long)targetSum - root->val) + 
               count(root->right, (long long)targetSum - root->val);
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) { return 0; }
        return count(root, targetSum) + 
               pathSum(root->left, targetSum) + 
               pathSum(root->right, targetSum);
    }
};