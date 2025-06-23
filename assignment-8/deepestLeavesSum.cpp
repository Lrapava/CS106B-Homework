// https://leetcode.com/problems/deepest-leaves-sum/description

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
    int deepestLeavesSum(TreeNode* root) {
        deepestLeavesSumHelper(root, 0);
        return mp[max_depth];
    }
private:

    void deepestLeavesSumHelper(TreeNode* root, int depth) {
        mp[depth] += root->val;
        if (root->left != nullptr)
            deepestLeavesSumHelper(root->left,  depth+1);
        if (root->right != nullptr)
            deepestLeavesSumHelper(root->right, depth+1);
        max_depth = max(max_depth, depth);
    }

    unordered_map <int, int> mp;
    int max_depth = 0;
};
