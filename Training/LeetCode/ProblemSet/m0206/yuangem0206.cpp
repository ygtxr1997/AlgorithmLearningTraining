/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 快慢找中点
// 翻转后半段
// 前后段比较
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* ret = new ListNode(-1); // 头节点
        while (head) {
            ListNode* first = ret->next, *nxt = head->next;
            ret->next = head;
            head->next = first;
            head = nxt;
        }
        return ret;
    }
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode* left = new ListNode(-1);
        left->next = head;
        ListNode* slow = left, *fast = left;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* mid = slow;
        bool bOdd = (fast == nullptr);
        if (!bOdd && mid->val != mid->next->val) return false; // 中间的提前比较
        ListNode* right = reverseList(mid->next);
        while (left != mid) {
            if (left->val != right->val) return false;
            left = left->next, right = right->next;
        }
        return true;
    }
};