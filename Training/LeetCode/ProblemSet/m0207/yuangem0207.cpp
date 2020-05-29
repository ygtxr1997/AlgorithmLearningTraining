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
        ListNode* nA = headA, *nB = headB;
        int lA = 0, lB = 0;
        while (nA) nA = nA->next, lA++;
        while (nB) nB = nB->next, lB++;
        ListNode* big = lA > lB ? headA : headB;
        ListNode* small = lA > lB ? headB : headA;
        int dif = abs(lA - lB);
        for (int i = 0; i < dif; ++i) big = big->next;
        while (big && small) {
            if (big == small) return big;
            big = big->next, small = small->next;
        }
        return nullptr;
    }
};