#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 103;
const int maxm = 2020;
const int offset = 100 * 2000 / 2; // 重量偏移, 负数向右偏移为正数才可以用01背包处理
const int INF = 0x3f3f3f3f;

// 每头牛有2个维度, 并且可以选或不选, 所以可以转化为01背包问题处理
// dp[i][j]:前i头牛重量为j时的最大价值
// dp[i+1][j] = max{ dp[i][j-F[i]] + S[i], dp[i][j] } 分别对应不选牛i和选牛i
// 滚动数组优化
// dp[j] = max{ last[j-F[i]] + S[i], last[j] }
// 此题坑点1: 最大范围是-100*1000~100*1000, 而不是-1000~1000
// 此题坑点2: dp时左右界都要判断, j - F[i] >= 0 && j - F[i] <= maxn*maxm
int N; // 牛数
int S[maxn], F[maxn]; // S看作价值, F看作重量
int dp[maxn * maxm]; // dp[i][j]:前i头牛重量为j时的最大价值
int last[maxn * maxm]; // 上一行
int solve(void) {
    int ans = offset;
    // 初始化
    for (int j = 0; j < maxn * maxm; ++j) {
        last[j] = dp[j] = -INF; 
    }
    for (int i = 0; i < N; ++i) {
        last[offset] = dp[offset] = 0;
        for (int j = 1; j < maxn * maxm; ++j) {
            if (j - F[i] >= 0 && j - F[i] < maxn * maxm) {
                if (last[j - F[i]] != -INF)
                    dp[j] = max(last[j], last[j - F[i]] + S[i]);
                else dp[j] = last[j];
            } else {
                dp[j] = last[j];
            }
            if (ans < dp[j] + j && j >= offset && dp[j] >= 0) {
                ans = dp[j] + j;
                //printf("(%d,%d):%d\n", i + 1, j - offset, dp[j]);
            }
            //if (dp[j] != -INF) printf("(%d,%d):%d\n", i + 1, j - offset, dp[j]);
        }
        memcpy(last, dp, sizeof(last));
    }
    return ans - offset;
}
int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d%d", &S[i], &F[i]);
        printf("%d\n", solve());
    }
    return 0;
}