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
    // 前缀和+哈希+根左右遍历
    unordered_map<int, int> hash;
    int dfs(TreeNode* node, int curSum, int sum) {
        if (!node) return 0;
        curSum += node->val;
        int cnt = 0;
        if (hash.count(curSum - sum)) cnt += hash[curSum - sum];
        hash[curSum]++;
        cnt += dfs(node->left, curSum, sum);
        cnt += dfs(node->right, curSum, sum);
        hash[curSum]--;
        return cnt;
    }
    int pathSum(TreeNode* root, int sum) {
        hash[0] = 1;
        return dfs(root, 0, sum);
    }
};