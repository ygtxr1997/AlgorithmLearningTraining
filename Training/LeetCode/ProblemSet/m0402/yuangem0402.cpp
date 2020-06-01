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
    TreeNode* makeBST(vector<int>& nums, int left, int right) {
        if (left == right) return nullptr;
        int mid = (left + right) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        TreeNode* lson = makeBST(nums, left, mid);
        TreeNode* rson = makeBST(nums, mid + 1, right);
        root->left = lson;
        root->right = rson;
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return makeBST(nums, 0, nums.size());
    }
};