#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxt = 1010;
const int maxn = 103;
const int mod = 1e6;

// 多重集组合数
// dp[i][j]:前i种家族组成元素个数为j的集合, 一共有多少种方案
// dp[i+1][j] = Σ(k=0, min(j,cnt[i]))dp[i][j-k]
//            = Σ(k=1, min(j,cnt[i]))dp[i][j-k] + dp[i][j]
//            let k' = k - 1,
//            = Σ(k'=0, min(j-1, cnt[i]-1))dp[i][j-(k'+1)] + dp[i][j]
//            = Σ(k=0, min(j-1, cnt[i]-1))dp[i][j-k-1] + dp[i][j]           ......(1)
// while,
// dp[i+1][j-1] = Σ(k=0, min(j-1,cnt[i]))dp[i][j-1-k]
//              = Σ(k=0, min(j-1,cnt[i]-1))dp[i][j-1-k] + dp[i][j-1-cnt[i]] ......(2)
// because (1),(2),
// dp[i+1][j] = dp[i+1][j-1] - dp[i][j-1-cnt[i]] + dp[i][j]
// 滚动数组优化,
// dp[j] = dp[j-1] - last[j-1-cnt[i]] + last[j]
int T, A, S, B; // 家族数, 总人数, 集合最小元素数, 集合最大元素数
int cnt[maxt]; // 每个家族的人数
int dp[maxt * maxn]; // dp[i][j]:前i种家族组成元素个数为j的集合, 一共有多少种方案
int last[maxt * maxn];
int solve(void) {
    memset(last, 0, sizeof(last));
    last[0] = 1;
    int ans = 0;
    for (int i = 0; i < T; ++i) { // 遍历行
        dp[0] = 1;
        for (int j = 1; j <= B; ++j) { // 遍历列
            if (j - 1 - cnt[i] >= 0) {
                dp[j] = dp[j - 1] + last[j] - last[j - 1 - cnt[i]];
            } else {
                dp[j] = dp[j - 1] + last[j];
            }
            dp[j] %= mod;
            //printf("(%d, %d): %d\n", i, j, dp[j]);
            if (i == T - 1 && j >= S) ans = (ans + dp[j]) % mod;
        }
        memcpy(last, dp, sizeof(dp));
    }
    return ((ans % mod) + mod) % mod;
}
int main(void) {
    while (scanf("%d%d%d%d", &T, &A, &S, &B) != EOF) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < A; ++i) {
            int fam;
            scanf("%d", &fam);
            cnt[fam - 1]++;
        }
        printf("%d\n", solve());
    }
    return 0;
}