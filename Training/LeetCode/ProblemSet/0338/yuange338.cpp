class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> dp(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            // 利用前面已求得的结果
            dp[i] = dp[i >> 1] + (i & 1);
        }
        return dp;
    }
};