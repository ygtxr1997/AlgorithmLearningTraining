#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 2010;

int N;
int V[maxn];
int dp[maxn][maxn]; // dp[i][j]:还剩i到j时能获取的最大利润
// 区间dp
int solve(void) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= N; ++i) dp[i][i] = V[i] * N; // 只剩一个
    for (int len = 1; len <= N; ++len) { // 枚举区间长度
        for (int i = 1; i + len <= N; ++i) {
            int j = i + len;
            dp[i][j] = max(dp[i + 1][j] + V[i] * (N - len),
                            dp[i][j - 1] + V[j] * (N - len));
        }
    }
    return dp[1][N];
}

int main(void) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &V[i]);
    }
    printf("%d\n", solve());
    return 0;
}