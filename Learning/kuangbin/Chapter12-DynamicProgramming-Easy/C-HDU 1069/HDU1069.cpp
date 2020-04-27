#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
#define TES
const int maxn = 32;

// dp[i][j]:以i号为顶, j边为高的最高高度
// dp[i][j] = max{ dp[x][y] }, x的非y边均大于i的非j边
int N; // N blocks
int X[maxn], Y[maxn], Z[maxn];
int dp[maxn][3]; // 以i号为顶, j边为高的最高高度

int solve(void) {
    for (int i = 1; i <= N; ++i) {
        dp[i][0] = X[i];
        dp[i][1] = Y[i];
        dp[i][2] = Z[i];
    }
    for (int num = 1; num <= 3 * N; ++num) {
        for (int i = 1; i <= N; ++i) {
            for (int h = 0; h < 3; ++h) { 
                if (h == 0) { // 第i块以X为高
                    for (int j = 1; j <= N; ++j) {
                        if ((Y[j] > Y[i] && Z[j] > Z[i]) || (Z[j] > Y[i] && Y[j] > Z[i])) // 第j块以X为高
                            dp[i][0] = max(dp[i][0], dp[j][0] + X[i]);
                        if ((Z[j] > Y[i] && X[j] > Z[i]) || (X[j] > Y[i] && Z[j] > Z[i])) // 第j块以Y为高
                            dp[i][0] = max(dp[i][0], dp[j][1] + X[i]);
                        if ((X[j] > Y[i] && Y[j] > Z[i]) || (Y[j] > Y[i] && X[j] > Z[i])) // 第j块以Z为高
                            dp[i][0] = max(dp[i][0], dp[j][2] + X[i]);
                    }
                } else if (h == 1) { // 第i块以Y为高
                    for (int j = 1; j <= N; ++j) {
                        if ((Y[j] > X[i] && Z[j] > Z[i]) || (Z[j] > X[i] && Y[j] > Z[i])) // 第j块以X为高
                            dp[i][1] = max(dp[i][1], dp[j][0] + Y[i]);
                        if ((Z[j] > X[i] && X[j] > Z[i]) || (X[j] > X[i] && Z[j] > Z[i])) // 第j块以Y为高
                            dp[i][1] = max(dp[i][1], dp[j][1] + Y[i]);
                        if ((X[j] > X[i] && Y[j] > Z[i]) || (Y[j] > X[i] && X[j] > Z[i])) // 第j块以Z为高
                            dp[i][1] = max(dp[i][1], dp[j][2] + Y[i]);
                    }
                } else { // 第i块以Z为高
                    for (int j = 1; j <= N; ++j) {
                        if ((Y[j] > Y[i] && Z[j] > X[i]) || (Z[j] > Y[i] && Y[j] > X[i])) // 第j块以X为高
                            dp[i][2] = max(dp[i][2], dp[j][0] + Z[i]);
                        if ((Z[j] > Y[i] && X[j] > X[i]) || (X[j] > Y[i] && Z[j] > X[i])) // 第j块以Y为高
                            dp[i][2] = max(dp[i][2], dp[j][1] + Z[i]);
                        if ((X[j] > Y[i] && Y[j] > X[i]) || (Y[j] > Y[i] && X[j] > X[i])) // 第j块以Z为高
                            dp[i][2] = max(dp[i][2], dp[j][2] + Z[i]);
                    }
                }
            }
        }
    }
    int ans = -1;
    for (int i = 1; i <= N; ++i)
        for (int h = 0; h < 3; ++h)
            ans = max(ans, dp[i][h]);
    return ans;
}

int main(void) {
    #ifdef TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int T = 1;
    while (scanf("%d", &N) && N != 0) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
        }
        printf("Case %d: ", T++);
        printf("maximum height = %d\n", solve());
    }
    return 0;
}