class Solution {
public:
    typedef struct node {
        node(){}
        node(int x, int y) : val(x), pos(y) {}
        int val, pos;
    } node;
    vector<int> numsSameConsecDiff(int N, int K) {
        if (N == 1) return vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> ret;
        queue<node> qu;
        for (int i = 1; i <= 9; i++) qu.push(node(i, 1));
        while (!qu.empty()) {
            int v = qu.front().val, p = qu.front().pos;
            qu.pop();
            if (p == N) {
                ret.push_back(v); // 找到一个长度为N的数
                continue;
            }
            if ((v % 10) - K >= 0) {
                qu.push(node(v * 10 + ((v % 10) - K), p + 1));
            }
            if (K != 0 && (v % 10) + K <= 9) { // 注意排除K为0的情况, 会重复计算
                qu.push(node(v * 10 + ((v % 10) + K), p + 1));
            }
        }
        return ret;
    }
};