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
    int kthToLast(ListNode* head, int k) {
        ListNode* pre = head, *nxt = head;
        for (int i = 0; i < k; ++i) nxt = nxt->next;
        while (nxt) {
            pre = pre->next;
            nxt = nxt->next;
        }
        return pre->val;
    }
};