#include <iostream>
#include <cstring>
#include <algorithm>
#define TES
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 510;
const int maxw = 10010;

int T;
int E, F; // 1<=E<=F<=10000
int N; // 1<=N<=500
int P[maxn]; // value
int W[maxn]; // weight
int dp[maxw]; // dp[i] = 质量为i时的最小value
// 完全背包问题
// 前x种货币加入钱罐中, 逐次求出钱罐中各个weight对应的最小value
int solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int x = 1; x <= N; ++x) {
        for (int i = W[x]; i <= F - E; ++i) {
            dp[i] = min(dp[i], dp[i - W[x]] + P[x]);
        }
    }
    return dp[F - E];
}

int main(void) {
    #ifdef TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &E, &F, &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%d%d", &P[i], &W[i]);
        }
        int ans = solve();
        if (ans == INF) printf("This is impossible.\n");
        else printf("The minimum amount of money in the piggy-bank is %d.\n", ans);
    }
    return 0;
}