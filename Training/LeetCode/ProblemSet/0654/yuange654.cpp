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
    TreeNode* createTree(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        if (left == right) {
            TreeNode* cur = new TreeNode(nums[left]);
            return cur;
        }
        int maxInd, maxVal = INT_MIN;
        for (int i = left; i <= right; ++i) {
            if (nums[i] > maxVal) {
                maxVal = nums[i];
                maxInd = i;
            }
        }
        TreeNode* cur = new TreeNode(maxVal);
        cur->left = createTree(nums, left, maxInd - 1);
        cur->right = createTree(nums, maxInd + 1, right);
        return cur;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return createTree(nums, 0, nums.size() - 1);
    }
};