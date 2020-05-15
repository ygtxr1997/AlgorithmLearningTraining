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
    void dfs(TreeNode* node, vector<int>& vec) {
        if (!node) return;
        if (!node->left && !node->right) {
            vec.push_back(node->val);
            return;
        }
        dfs(node->left, vec);
        dfs(node->right, vec);
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> vec1, vec2;
        dfs(root1, vec1);
        dfs(root2, vec2);
        if (vec1.size() != vec2.size()) return false;
        for (int i = 0; i < vec1.size(); ++i)
            if (vec1[i] != vec2[i]) return false;
        return true;
    }
};