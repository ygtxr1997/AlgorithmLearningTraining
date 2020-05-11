class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        const int maxn = 503;
        int n = A.size();
        vector<int> dp(n, 0); // dp[i]:下标0~下标i范围内数组能分割出的最大总和
        dp[0] = A[0];
        for (int i = 1; i < n; ++i) {
            int curMax = A[i];
            for (int j = 1; j <= K && i - j + 1 >= 0; ++j) {
                curMax = max(curMax, A[i - j + 1]); // 根据j节点向左遍历更新当前max的值, 不需要BIT查询区间最大值
                if (i - j + 1 == 0) {
                    dp[i] = max(dp[i], j * curMax);
                } else {
                    dp[i] = max(dp[i], dp[i - j] + j * curMax);
                }
            }
        }
        return dp[n - 1];
    }
};