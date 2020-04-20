#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace::std;
const int maxn = 1e5 + 30;
typedef pair<double, double> pdd;

int T;
int W, H, L, U, R, D;
double dp[maxn]; // 本行
double last[maxn]; // 上一行
double bfs(void) {
    for (int i = 0; i <= W; ++i) last[i] = dp[i] = 0;
    last[1] = 2;
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= W; ++j) {
            if (i >= U && i <= D && j >= L && j <= R) {
                dp[j] = 0;
            } else if (i == H) {
                if (j == 1) dp[j] = last[j] * 0.5;
                else if (j == W) dp[j] = dp[j - 1] + last[j];
                else dp[j] = dp[j - 1] + last[j] * 0.5;
            } else if (j == W) {
                dp[j] = dp[j - 1] * 0.5 + last[j];
            } else {
                dp[j] = dp[j - 1] * 0.5 + last[j] * 0.5;
            }
        }
        memcpy(last, dp, sizeof(dp));
    }
    return dp[W];
}

int main(void) {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d%d%d", &W, &H, &L, &U, &R, &D);

        printf("Case #%d: %lf\n", t, bfs());
    }
    return 0;
}