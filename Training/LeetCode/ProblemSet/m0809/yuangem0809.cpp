class Solution {
public:
    typedef struct node {
        int left, right; // 左括号总个数, 右括号总个数
        int cur; // 左括号未匹配个数
        string str;
        node(){}
        node(int l, int r, int c, string s) : left(l), right(r), cur(c), str(s) {}
    } node;
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        queue<node> qu;
        node start;
        start.left = 1, start.right = 0, start.cur = 1, start.str = "(";
        qu.push(start);
        while (!qu.empty()) {
            int left = qu.front().left, right = qu.front().right;
            int cur = qu.front().cur;
            string str = qu.front().str;
            qu.pop();
            if (right == n) { // 终点
                ret.push_back(str);
                continue;
            }
            // left
            if (left < n) qu.push(node(left + 1, right, cur + 1, str + "("));
            // right
            if (right < left) qu.push(node(left, right + 1, cur - 1, str + ")"));
        }
        return ret;
    }
};