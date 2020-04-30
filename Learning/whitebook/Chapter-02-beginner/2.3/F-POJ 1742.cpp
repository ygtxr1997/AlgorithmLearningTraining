#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 103;
const int maxm = 100010;

// 多重背包问题, 
// dp[i][j]:前i种硬币凑成总额j,第i种硬币的剩余个数,若不可能凑成则值为-1
//              | C[i],                 dp[i][j]>=0
// dp[i+1][j] = | -1,                   j<A[i]或dp[i+1][j-A[i]]<=0
//              | dp[i+1][j-A[i]]-1,    其他
// 由于i+1的状态只和i+1以及i有关, 所以可以用滚动数组优化
int n, m; // 硬币个数, 期望总额
int A[maxn], C[maxn]; // 面额, 个数
int dp[maxm];
int solve(void) {
    memset(dp, -1, sizeof(dp)); // 默认是-1
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) { // 一定要从0开始
            if (dp[j] >= 0) dp[j] = C[i];
            else if (j < A[i] || dp[j - A[i]] <= 0) dp[j] = -1;
            else dp[j] = dp[j - A[i]] - 1;
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; ++j) if (dp[j] >= 0) ans++;
    return ans;
}
int main(void) {
    while (scanf("%d%d", &n, &m) && n + m != 0) {
        for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &C[i]);
        printf("%d\n", solve());
    }
    return 0;
}