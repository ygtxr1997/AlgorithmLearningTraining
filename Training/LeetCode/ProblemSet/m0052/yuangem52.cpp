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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int l1 = 0, l2 = 0;
        ListNode* h1 = headA, *h2 = headB;
        while (h1) l1++, h1 = h1->next;
        while (h2) l2++, h2 = h2->next;
        if (l2 > l1) while (l2 - l1 > 0) headB = headB->next, l2--;
        if (l1 > l2) while (l1 - l2 > 0) headA = headA->next, l1--;
        while (headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};