#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010; // 1000010
const int mod = 1e9;
typedef long long ll;

// 完全背包问题, 会TLE
// dp[i][j]:前i种物品组成j的总方案数, 使用滚动数组优化
// dp[i + 1][j] = dp[i][j] + dp[i + 1][j - v[i]]
// dp[j] = dp[j] + dp[j - v[i]];
int N;
ll dp[maxn]; // dp[i][j]:前i种物品组成j的总方案数, 使用滚动数组优化
ll v[30];
int solve(void) {
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < 30; ++i) {
        v[i] = (1 << i); // 每种物品的价值都是2的幂
    }
    dp[0] = 1;
    for (int i = 0; i < 30; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (j >= v[i]) dp[j] = dp[j] + dp[j - v[i]];
            else dp[j] = dp[j];
            dp[j] %= mod;
        }
    }
    return dp[N];
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        printf("%d\n", solve());
    }
    return 0;
}