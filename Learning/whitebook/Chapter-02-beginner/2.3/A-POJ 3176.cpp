#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 360;

// 数塔问题, 从下往上dp
int N;
int dp[maxn][maxn];
int solve(void) {
    for (int i = N - 1; i >= 1; --i) {
        for (int j = i; j >= 1; --j) {
            dp[i][j] += max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }
    return dp[1][1];
}
int main(void) {
    while (scanf("%d", &N) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= i; ++j) {
                scanf("%d", &dp[i][j]);
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}