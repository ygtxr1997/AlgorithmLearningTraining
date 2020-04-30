#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxt = 1010;
const int maxw = 32;

// dp[i][j]:来到i位置, 还有j步可走
int T, W;
int apple[maxt];
int dp[maxt][maxw];
int solve(void) {
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= T; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (j == 0) dp[i][j] = dp[i - 1][j]; // 还有0步可走
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]);
            if (j % 2 + 1 == apple[i]) dp[i][j]++; // 当前位置就是苹果所在的位置
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

int main(void) {
    while (scanf("%d%d", &T, &W) != EOF) {
        memset(apple, 0, sizeof(apple));
        for (int i = 1; i <= T; ++i) {
            scanf("%d", &apple[i]);
        }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}