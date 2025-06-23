// https://leetcode.com/problems/binary-tree-maximum-path-sum/description/

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
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }

private:
    int dfs(TreeNode* node, int& maxs) {
        if (node == nullptr) {
        	return 0;
        }

        int l = max(0, dfs(node->left, maxs));
        int r = max(0, dfs(node->right, maxs));
        maxs = max(maxs, node->val + l + r);

        return node->val + max(l, r);
    }
};
