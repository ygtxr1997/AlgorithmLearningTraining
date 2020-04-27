#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 30010;

// 看似是最长递减子序列，其实是最长递增子序列
// 优化版LIS
int N;
int vec[maxn];
int dp[maxn]; // dp[i]:长度为i的递增子序列中, 后出现并且也是最小的末尾数字
int solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    int len = 2;
    dp[1] = vec[1];
    for (int i = 2; i <= N; ++i) { // 二分查找第一个比vec[i]大的数
        int* p = upper_bound(dp + 1, dp + len, vec[i]);
        int pos = p - dp;
        if (pos == len) len++;
        dp[pos] = vec[i];
    }
    return len - 1;
}

int main(void) {
    while(scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &vec[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}