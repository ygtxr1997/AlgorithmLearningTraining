/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<ListNode*> listOfDepth(TreeNode* tree) {
        vector<ListNode*> ret;
        queue<TreeNode*> qu;
        qu.push(tree);
        int size = 1;
        while (!qu.empty()) {
            ListNode* head = nullptr, *lNode = nullptr;
            int nxtSize = 0;
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = qu.front();
                qu.pop();
                ListNode* nNode = new ListNode(cur->val);
                if (!head) head = nNode;
                if (lNode) lNode->next = nNode;
                lNode = nNode;
                if (cur->left) {
                    qu.push(cur->left);
                    nxtSize++;
                }
                if (cur->right) {
                    qu.push(cur->right);
                    nxtSize++;
                }
            }
            size = nxtSize;
            ret.push_back(head);
        }
        return ret;
    }
};