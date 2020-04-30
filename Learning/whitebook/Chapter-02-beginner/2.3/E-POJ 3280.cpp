#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxm = 2020;
const int maxn = 27;
const int INF = 0x3f3f3f3f;

// 区间dp, 第二维既可以设为长度也可以设为区间终点,
// 但是最好画一下图看看更新顺序
int N, M;
char str[maxm];
int Add[maxn], Del[maxn]; // 代价
int dp[maxm][maxm];
// dp[i][j]:起点为i, 长度为j的最小回文代价
int solve2(void) {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < M; ++i) dp[i][0] = dp[i][1] = 0; // 长度为1也是回文
    for (int j = 2; j <= M; ++j) { // 区间长度
        for (int i = 0; i + j - 1 < M; ++i) { // 区间起点
            if (str[i] == str[i + j - 1]) dp[i][j] = dp[i + 1][j - 2];
            // 这里不能用else
            // 对于str[i]
            dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] 
                + min(Add[str[i] - 'a'], Del[str[i] - 'a']));
            // 对于str[i+j-1]
            dp[i][j] = min(dp[i][j], dp[i][j - 1]
                + min(Add[str[i + j - 1] - 'a'], Del[str[i + j - 1] - 'a']));
        }
    }
    return dp[0][M];
}
// dp[i][j]:i是区间左端点, j是区间右端点
int solve(void) {
    memset(dp, 0x3f, sizeof(dp)); // 这里也容易WA, 不能直接设为0x3f, 因为可能会访问dp[5][4]
    // 最好画一下图, 看看更新顺序
    for (int i = 0; i < M; ++i) dp[i][i] = dp[i][i - 1] = 0;
    for (int i = M - 1; i >= 0; i--) {
        for (int j = i + 1; j < M; ++j) {
            if (str[i] == str[j]) dp[i][j] = dp[i + 1][j - 1];
            dp[i][j] = min(dp[i][j], dp[i + 1][j]
                + min(Add[str[i] - 'a'], Del[str[i] - 'a']));
            dp[i][j] = min(dp[i][j], dp[i][j - 1]
                + min(Add[str[j] - 'a'], Del[str[j] - 'a']));
        }
    }
    return dp[0][M - 1];
}
int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        // 因为输入格式WA了好几次...
        scanf("%s", str);
        for (int i = 0; i < N; ++i) {
            char c;
            cin >> c;
            scanf("%d%d", &Add[c - 'a'], &Del[c - 'a']);
        }
        printf("%d\n", solve2());
    }
    return 0;
}