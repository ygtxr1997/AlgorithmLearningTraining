#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

int N;
int vec[maxn];
int dp[maxn]; // dp[i]:以i结尾的最长递增序列长度
int solve(void) {
    memset(dp, 0, sizeof(dp));
    int ans = 1;
    dp[1] = 1;
    for (int i = 2; i <= N; ++i) {
        int cur_max = 0;
        for (int j = 1; j < i; ++j) {
            if (vec[j] < vec[i]) cur_max = max(cur_max, dp[j]);
        }
        dp[i] = cur_max + 1;
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main(void) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &vec[i]);
    }
    printf("%d\n", solve());
    return 0;
}