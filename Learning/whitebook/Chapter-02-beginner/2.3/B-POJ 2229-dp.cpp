#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010; // 1000010
const int mod = 1e9;
typedef long long ll;

// 定义dp[i]:i由1,2,4,8,...,组成的方案总数
// 若i为奇数, 则dp[i] = dp[i-1]
// 若i为偶数, 且组成的数字包含1, 则一定至少包含2个1, 有dp[i-2]种
// 若i为偶数, 且组成的数字不包含1, 有dp[i / 2]种
int N;
ll dp[maxn];
int solve(void) {
    memset(dp, 0, sizeof(dp));
    dp[1] = dp[0] = 1;
    for (int i = 2; i <= N; ++i) {
        if (i % 2 == 1) dp[i] = dp[i - 1];
        else dp[i] = dp[i / 2] + dp[i - 2];
        dp[i] %= mod;
    }
    return dp[N];
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        printf("%d\n", solve());
    }
    return 0;
}