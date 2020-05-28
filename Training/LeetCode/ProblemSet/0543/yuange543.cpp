/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int ans = -1;
    int dfs(TreeNode* node) {
        if (!node) return 0;
        int L = dfs(node->left);
        int R = dfs(node->right);
        ans = max(ans, L + R + 1);
        return 1 + max(L, R);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        dfs(root);
        return ans - 1;
    }
};