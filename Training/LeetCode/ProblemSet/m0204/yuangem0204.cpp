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
    void headInsert(ListNode* head, ListNode* target) { // 头插法
        ListNode* first = head->next;
        head->next = target;
        target->next = first;
    }
    ListNode* partition(ListNode* head, int x) {
        ListNode* small = new ListNode(-1); // 小分组头节点
        ListNode* big = new ListNode(-1); // 大分组头节点
        ListNode* smallTail = nullptr; // 小分组尾节点
        ListNode* node = head;
        while (node) {
            ListNode* nxt = node->next;
            if (node->val < x) {
                if (!smallTail) smallTail = node;
                headInsert(small, node);
            } else {
                headInsert(big, node);
            }
            node = nxt;
        }
        if (smallTail) smallTail->next = big->next;
        return smallTail ? small->next : big->next;
    }
};