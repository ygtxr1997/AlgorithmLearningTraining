class Solution {
public:
    int waysToStep(int n) {
        const int mod = 1000000007;
        vector<long long> dp(n + 1);
        dp[1] = 1;
        if (n >= 2) dp[2] = 2;
        if (n >= 3) dp[3] = 4;
        for (int i = 4; i <= n; ++i) {
            dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % mod;
        }
        return dp[n];
    }
};