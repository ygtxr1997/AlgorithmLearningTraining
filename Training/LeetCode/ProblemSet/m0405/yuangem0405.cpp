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
    // 左根右为升序
    long long last = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        if (!root->left && !root->right) {
            long long cur = root->val;
            if (cur <= last) return false;
            last = cur;
            return true;
        }
        if (!isValidBST(root->left)) return false;
        long long cur = root->val;
        if (cur <= last) return false;
        last = cur;
        if (!isValidBST(root->right)) return false;
        return true;
    }
};