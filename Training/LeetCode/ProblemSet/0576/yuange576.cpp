class Solution {
public:
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int findPaths(int m, int n, int N, int ii, int jj) {
        if (m == 1 && n == 1) return N > 0 ? 4 : 0;
        const int mod = 1e9 + 7;
        long long dp[53][53][53] = { 0 }; // 三维dp, dp[i][j][k]:来到(i,j)还能走k步的总方案数
        for (int k = 1; k <= N; ++k) {
            dp[0][0][k] = dp[0][n - 1][k] = dp[m - 1][0][k] = dp[m - 1][n - 1][k] = 2;
            if (m == 1) dp[0][0][k]++, dp[0][n - 1][k]++;
            if (n == 1) dp[0][0][k]++, dp[m - 1][0][k]++;
            for (int i = 1; i < n - 1; ++i) dp[0][i][k]++, dp[m - 1][i][k]++;
            for (int i = 1; i < m - 1; ++i) dp[i][0][k]++, dp[i][n - 1][k]++;
        }
        for (int k = 2; k <= N; ++k) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int op = 0; op < 4; ++op) {
                        int ni = i + dir[op][0], nj = j + dir[op][1];
                        if (ni < 0 || ni >= m || nj < 0 || nj >= n) continue;
                        dp[i][j][k] = (dp[i][j][k] + dp[ni][nj][k - 1]) % mod;
                    }
                }
            }
        }
        return dp[ii][jj][N] % mod;
    }
};