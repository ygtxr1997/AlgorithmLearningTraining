#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

// dp[i][j] = min{ same, dp[i - 1][j + 1] + 1}
// 其中same代表点(i, j)往上的列与往右的行最多相同字母的个数
int n;
char matrix[maxn][maxn];
int dp[maxn][maxn]; // dp[i][j]:以(i, j)为左下角的最大对称矩阵的边长
int solve(void) {
    memset(dp, 0, sizeof(dp));
    int ans = 1;
    for (int k = 1; k <= n; ++k) dp[1][k] = dp[k][n] = 1; // 初始化
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n - 1; ++j) {
            int x = i - 1, y = j + 1;
            while (x >= 0 && y <= n && matrix[x][j] == matrix[i][y]) {
                x--;
                y++;
            } 
            int same = i - x;
            if (same > dp[i - 1][j + 1]) dp[i][j] = dp[i - 1][j + 1] + 1;
            else dp[i][j] = same;
            ans = max(ans, dp[i][j]);
        }
    } 
    return ans;
}

int main(void) {
    while (scanf("%d", &n) && n != 0) {
        for (int i = 1; i <= n; ++i) {
            getchar(); // 获取换行
            for (int j = 1; j <= n; ++j) {
                scanf("%c", &matrix[i][j]);
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}