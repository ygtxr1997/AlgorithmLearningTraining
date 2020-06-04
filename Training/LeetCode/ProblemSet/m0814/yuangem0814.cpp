class Solution {
public:
    int dp[40][40][2]; // dp[i][j][b]:i~j范围内值为b的总方法数
    string str;
    // 记忆化搜索
    int dfs(int l, int r, int b) {
        if (l == r) return dp[l][r][b] = (str[l] == b + '0' ? 1 : 0);
        if (dp[l][r][b] != -1) return dp[l][r][b];
        int cnt = 0;
        for (int i = l + 1; i < r; i += 2) {
            if (str[i] == '&' && b == 1)
                cnt += dfs(l, i - 1, 1) * dfs(i + 1, r, 1);
            else if (str[i] == '&' && b == 0)
                cnt += dfs(l, i - 1, 0) * dfs(i + 1, r, 0)
                        + dfs(l, i - 1, 0) * dfs(i + 1, r, 1)
                        + dfs(l, i - 1, 1) * dfs(i + 1, r , 0);
            else if (str[i] == '|' && b == 1)
                cnt += dfs(l, i - 1, 1) * dfs(i + 1, r, 1)
                        + dfs(l, i - 1, 0) * dfs(i + 1, r, 1)
                        + dfs(l, i - 1, 1) * dfs(i + 1, r , 0);
            else if (str[i] == '|' && b == 0)
                cnt += dfs(l, i - 1, 0) * dfs(i + 1, r, 0);
            else if (str[i] == '^' && b == 1)
                cnt += dfs(l, i - 1, 0) * dfs(i + 1, r, 1)
                        + dfs(l, i - 1, 1) * dfs(i + 1, r, 0);
            else if (str[i] == '^' && b == 0)
                cnt += dfs(l, i - 1, 0) * dfs(i + 1, r, 0)
                        + dfs(l, i - 1, 1) * dfs(i + 1, r, 1);
        }
        return dp[l][r][b] = cnt;
    }
    int countEval(string s, int result) {
        if (s.size() == 1) return s[0] == '0' + result ? 1 : 0;
        memset(dp, -1, sizeof(dp));
        str = s;
        return dfs(0, s.size() - 1, result);
    }
};