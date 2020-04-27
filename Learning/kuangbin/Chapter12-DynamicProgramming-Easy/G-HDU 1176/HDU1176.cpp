#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define TES
using namespace::std;
const int maxn = 100010; // 100010
const int INF = 0x3f3f3f3f;

int n;
int dp[maxn][11]; // dp[i][j]:第i秒在j位置能获得的最多馅饼数
int maxTime;
// 转化为数塔问题, 从底往上计算
int solve(void) {
    for (int t = maxTime - 1; t >= 0; t--) {
        for (int pos = 0; pos <= 10; pos++) {
            int down_max = 0;
            if (pos < 10) down_max = max(down_max, 
                            max(dp[t + 1][pos], dp[t + 1][pos + 1]));
            if (pos > 0) down_max = max(down_max, 
                            max(dp[t + 1][pos], dp[t + 1][pos - 1]));
            dp[t][pos] += down_max;
        }
    }
    return dp[0][5];
}

int main(void) {
    #ifdef TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    while (scanf("%d", &n) && n != 0) {
        memset(dp, 0, sizeof(dp));
        maxTime = -1;
        for (int i = 1; i <= n; ++i) {
            int time, pos;
            scanf("%d%d", &pos, &time);
            dp[time][pos]++;
            maxTime = max(maxTime, time);
        }
        printf("%d\n", solve());
    }
    return 0;
}