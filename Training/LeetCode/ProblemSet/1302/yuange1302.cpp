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
    int deepestLeavesSum(TreeNode* root) {
        int sum = 0;
        queue<TreeNode*> qu;
        int level = 1;
        qu.push(root);
        while (!qu.empty()) {
            int nxt = 0, hasSon = 0;
            sum = 0;
            for (int i = 0; i < level; ++i) {
                TreeNode* cur = qu.front();
                sum += cur->val;
                qu.pop();
                if (cur->left) { qu.push(cur->left); nxt++; hasSon = 1; }
                if (cur->right) { qu.push(cur->right); nxt++; hasSon = 1; }
            }
            level = nxt;
            if (!hasSon) break;
        }
        return sum;
    }
};