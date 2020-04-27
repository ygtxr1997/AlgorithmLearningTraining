#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 10100;
const int INF = 0x3f3f3f3f;

// 二分优化版最长上升子序列
int N;
int vec[maxn];
int dp[maxn]; // dp[i]:长度为i的递增子序列的最后出现的元素
int solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    int len = 1;
    dp[1] = vec[1];
    for (int i = 2; i <= N; ++i) {
        // 这里必须用lower_bound而不能用upper_bound
        int* p = lower_bound(dp + 1, dp + len + 2, vec[i]);
        int pos = p - dp;
        if (pos > len) len++;
        dp[pos] = vec[i];
    }
    return len;
}

int main(void) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &vec[i]);
    }
    printf("%d\n", solve());
    return 0;
}