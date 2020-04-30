#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010; // 1000010
const int mod = 1e9;
typedef long long ll;

// 完全背包问题, 会TLE, 剪枝后1016ms擦线过
// dp[i][j]:前i种物品组成j的总方案数, 使用滚动数组优化
// dp[i + 1][j] = dp[i][j] + dp[i + 1][j - v[i]]
// dp[j] = dp[j] + dp[j - v[i]];
int N;
int h; // 最高位
int dp[maxn]; // dp[i][j]:前i种物品组成j的总方案数, 使用滚动数组优化
int v[30];
int solve(void) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < h; ++i) {
        if (v[i] > N) break; // 更大的就不用考虑了
        for (int j = v[i]; j <= N; ++j) { // 从v[i]开始遍历也会少许优化
            dp[j] = dp[j] + dp[j - v[i]];
            dp[j] %= mod;
        }
    }
    return dp[N];
}

int main(void) {
    for (int i = 0; i < 30; ++i) { // 初始化
        v[i] = (1 << i); // 每种物品的价值都是2的幂
        if (v[i] >= maxn) h = i;
    }
    while (scanf("%d", &N) != EOF) {
        printf("%d\n", solve());
    }
    return 0;
}