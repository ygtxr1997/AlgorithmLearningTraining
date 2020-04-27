#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// 记忆化搜索
int k, n;
int grid[maxn][maxn];
int dp[maxn][maxn]; // dp[i][j]:从(i, j)出发可以得到的最大值

int dfs(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    int cur_max = 0;
    for (int x = 1; x <= k; ++x) { // 每次最多走k步
        for (int op = 0; op < 4; ++op) {
            int n_i = dir[op][0] * x + i;
            int n_j = dir[op][1] * x + j;
            if (n_i >= 1 && n_i <= n && n_j >= 1 && n_j <= n
                && grid[n_i][n_j] > grid[i][j]) {
                cur_max = max(cur_max, dfs(n_i, n_j));
            }
        }
    }
    dp[i][j] = cur_max + grid[i][j];
    return dp[i][j];
}

int main(void) {
    while ((scanf("%d%d", &n, &k)) && (k + n) != -2) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &grid[i][j]);
            }
        }
        memset(dp, -1, sizeof(dp));
        printf("%d\n", dfs(1, 1));
    }
    return 0;
}