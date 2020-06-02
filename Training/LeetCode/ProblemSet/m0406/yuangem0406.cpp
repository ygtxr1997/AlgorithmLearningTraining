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
    TreeNode* last = nullptr;
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root) return nullptr;
        TreeNode* ret = nullptr;
        if (root->left) {
            ret = inorderSuccessor(root->left, p);
        }
        if (last == p) ret = root;
        last = root;
        if (root->right && !ret) {
            ret = inorderSuccessor(root->right, p);
        }
        return ret;
    }
};