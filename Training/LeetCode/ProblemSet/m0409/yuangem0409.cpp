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
    vector<vector<int>> ret;
    vector<int> vec;
    void dfs(TreeNode* node, vector<TreeNode*> choose) {
        if (!node) return;
        if (choose.empty()) {
            vec.push_back(node->val);
            ret.push_back(vec);
            vec.pop_back();
            return;
        }
        vec.push_back(node->val);
        for (int i = 0; i < choose.size(); ++i) {
            TreeNode* FF = choose[0];
            vector<TreeNode*> nxt(choose.begin() + 1, choose.end());
            copy(nxt.begin(), nxt.end(), choose.begin());
            choose.resize(nxt.size());
            choose.push_back(FF);
            if (FF->left) nxt.push_back(FF->left);
            if (FF->right) nxt.push_back(FF->right);
            dfs(FF, nxt);
        };
        vec.pop_back();
    }
    vector<vector<int>> BSTSequences(TreeNode* root) {
        if (!root) {
            ret.push_back(vector<int>());
            return ret;
        }
        vector<TreeNode*> choose;
        if (root->left) choose.push_back(root->left);
        if (root->right) choose.push_back(root->right);
        dfs(root, choose);
        return ret;
    }
};