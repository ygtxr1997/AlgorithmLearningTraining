#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000100;
const int INF = 0x7fffffff;

// dp[i][j]:前i个数字以i结尾, 分成j段, 的最大和
// dp[i][j] = max(dp[i-1][j], U(j-1<=k<i)dp[k][j-1]) + vec[i]
// 第j列的状态只和j列以及j-1列有关, 用两个数组分别保存j列和j-1列的状态
int m, n;
int vec[maxn];
int cur[maxn]; // dp[i][j]
int last[maxn]; // dp[0~i][j-1]中的最大值

int solve() {
    memset(cur, 0, sizeof cur);
    memset(last, 0, sizeof last);
    int ans;
    for (int j = 1; j <= m; ++j) {
        ans = -INF;
        for (int i = j; i <= n; ++i) { // 这里必须从j开始更新
            cur[i] = max(cur[i - 1], last[i - 1]) + vec[i];
            last[i - 1] = ans;
            ans = max(ans, cur[i]);
        }
    }
    return ans;
}

int main(void) {
    while (scanf("%d%d", &m, &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &vec[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}