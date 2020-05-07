// ---------------------------------------------------------------------
// 题目描述:
// 给定 n 个顶点组成的带权有向图的距离矩阵 d(I, j) (INF表示没有边).
// 要求从顶点 0 出发, 经过每个顶点恰好一次后再回到顶点0.
// 问经过边的总权重的最小值是多少.
// 2 <= n <= 15
// 0 <= d(i,j) <= 1000
// ---------------------------------------------------------------------
// 思路:
// 状态压缩dp
// dp[i][j]:i代表已经访问过的点的集合, j代表当前所在位置
// dp[i][j] = min{ dp[i∪{u}][u] + d(v,u) | u !∈ i}
// dp[V][0] = 0
// 根据递推式计算而不用递归
// ---------------------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 16;
const int INF = 0x3f3f3f3f;

// input
int n;
int d[maxn][maxn];

int dp[1 << maxn][maxn];

void print(int S, int v) {
    int mod = 1 << (n - 1);
    int val = dp[S][v];
    printf("S=");
    while (mod > 0) {
        printf("%d", (S & mod) == 0 ? 0 : 1);
        mod /= 2;
    }
    printf(" v=%d dp[S][v]=%d\n", v, val);
}

// 直接根据递推式计算
void solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    dp[(1 << n) - 1][0] = 0; // 初始条件

    for (int S = (1 << n) - 2; S >= 0; S--) {
        for (int v = 0; v < n; ++v) {
            for (int u = 0; u < n; ++u) {
                if (!(S >> u & 1)) { // S集合包括u
                    dp[S][v] = min(dp[S][v], dp[S | 1 << u][u] + d[v][u]);
                    printf("u=%d ", u);
                    print(S, v); 
                }
            }
        }
    }
    printf("%d\n", dp[0][0]);
}

int main(void) {
    n = 5;
    memset(d, 0x3f, sizeof(d));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    d[0][1] = 3;
    d[0][3] = 4;
    d[1][2] = 5;
    d[2][0] = 4;
    d[2][3] = 5;
    d[3][4] = 3;
    d[4][0] = 7;
    d[4][1] = 6;
    solve();
    return 0;
}