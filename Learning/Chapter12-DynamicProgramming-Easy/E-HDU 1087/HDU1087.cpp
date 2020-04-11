#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

int N;
int vec[maxn];
int dp[maxn];

int solve(void) {
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        dp[i] = vec[i];
        for (int j = 1; j < i; ++j) {
            if (vec[i] > vec[j]) dp[i] = max(dp[i], dp[j] + vec[i]);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main(void) {
    while (scanf("%d", &N) && N != 0) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &vec[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}