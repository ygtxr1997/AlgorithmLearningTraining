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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode* n1 = l1, *n2 = l2;
        ListNode* ret = nullptr, *nr = nullptr;
        int c = 0, g = 0; // 本位, 进位
        while (n1 && n2) {
            c = (n1->val + n2->val + g) % 10;
            g = (n1->val + n2->val + g) / 10;
            ListNode* nxt = new ListNode(c);
            if (!ret) ret = nxt;
            if (nr) nr->next = nxt;
            nr = nxt;
            n1 = n1->next;
            n2 = n2->next;
        }
        ListNode* rst = n1 ? n1 : n2;
        while (rst) {
            c = (rst->val + g) % 10;
            g = (rst->val + g) / 10;
            rst->val = c;
            nr->next = rst;
            nr = rst;
            rst = rst->next;
        }
        if (g > 0) {
            ListNode* tail = new ListNode(g);
            nr->next = tail;
        }
        return ret;
    }
};