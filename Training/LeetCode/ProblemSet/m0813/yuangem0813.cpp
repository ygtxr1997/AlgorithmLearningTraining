class Solution {
public:
    typedef struct node {
        int x, y, z;
        node(){}
        node(int a, int b, int c) : x(a), y(b), z(c) {}
        bool operator<(const node& n2) {
            if (x != n2.x) return x < n2.x;
            if (y != n2.y) return y < n2.y;
            return z < n2.z;
        }
        bool small(const node& n2) {
            return x < n2.x && y < n2.y && z < n2.z;
        }
    } node;
    int pileBox(vector<vector<int>>& box) {
        vector<node> Box;
        for (auto vec : box) Box.push_back(node(vec[0], vec[1], vec[2]));
        sort(Box.begin(), Box.end()); // 一定要先排序, 优先选较小的箱子, 贪心思想
        vector<int> dp(Box.size() + 1); // 以第i个箱子结尾的最高高度
        int res = 0;
        for (int i = 0; i < Box.size(); ++i) {
            dp[i + 1] = Box[i].z;
            for (int j = 0; j < i; ++j) {
                if (Box[j].small(Box[i])) {
                    dp[i + 1] = max(dp[i + 1], dp[j + 1] + Box[i].z);
                }
            }
            res = max(dp[i + 1], res);
        }
        return res;
    }
};