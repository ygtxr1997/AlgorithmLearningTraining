#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxk = 403;
const int maxa = 40010;

// 首先要贪心, 可以证明先处理限高小的才能保证结果最大, 然后就是个多重背包问题
// dp[i][j]:前i种石头达到高度j, 第i-1种石头的剩余数量
//              | c[i],                 dp[i][j]>=0
// dp[i+1][j] = | -1,                   j>a[i] || dp[i+1][j-h[i]]<=0
//              | dp[i+1][j-h[i]]-1,    others
// 滚动数组优化,
//         | c[i],          last[j]>=0
// dp[j] = | -1,            j>a[i] || dp[j-h[i]]<=0
//         | dp[j-h[i]]-1,  others
// 一直WA, 比较了几百组数据都没区别, 吐了
int K;
typedef struct node {
    // 这里用到了贪心, 必须先处理限高小的才能保证总高度最大
    bool operator<(const node& n2) { return a < n2.a; }
    int h, a, c;
} node;
node blocks[maxk];
int dp[maxa]; // i+1行
int last[maxa]; // 前一行
int solve(void) {
    sort(blocks, blocks + K);
    memset(last, -1, sizeof(last));
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < K; ++i) {
        dp[0] = blocks[i].c; // 高度为0时, 任何石头都不消耗
        for (int j = 1; j <= blocks[i].a; ++j) {
            if (last[j] >= 0) dp[j] = blocks[i].c;
            else if (dp[j - blocks[i].h] <= 0) dp[j] = -1;
            else dp[j] = dp[j - blocks[i].h] - 1;
            if (dp[j] >= 0) ans = max(ans, j);
            //printf("(%d,%d):%d | ", i + 1, j, dp[j]);
        }
        memcpy(last, dp, sizeof(last));
        memset(dp, -1, sizeof(dp));
    }
    return ans;
}

int main(void) {
    int t = 1;
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while (scanf("%d", &K) != EOF) {
        memset(blocks, 0, sizeof(blocks));
        for (int i = 0; i < K; ++i) {
            scanf("%d%d%d", &blocks[i].h, &blocks[i].a, &blocks[i].c);
        }
        //printf("Case %d: %d\n", t++, solve());
        printf("%d\n", solve());
    }
    return 0;
}