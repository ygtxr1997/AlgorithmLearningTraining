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
    void RML(TreeNode* node, int& sum) {
        if (!node) return;
        int v = node->val;
        if (node->right) RML(node->right, sum);
        sum += v;
        node->val = sum;
        if (node->left) RML(node->left, sum);
        return; 
    }
    TreeNode* bstToGst(TreeNode* root) {
        int sum = 0;
        RML(root, sum);
        return root;
    }
};