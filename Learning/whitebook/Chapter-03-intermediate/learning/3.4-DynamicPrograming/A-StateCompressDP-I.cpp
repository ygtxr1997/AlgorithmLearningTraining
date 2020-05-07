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

// 记忆化搜索
// 已经访问过的节点集合为S, 当前位置为v
int rec(int S, int v) {
    print(S, v);
    if (dp[S][v] >= 0) return dp[S][v];
    if (S == (1 << n) - 1 && v == 0) {
        return dp[S][v] = 0; // 所有节点都访问过且回到了0号节点
    }
    int res = INF;
    for (int u = 0; u < n; ++u) {
        if (!((S >> u) & 1)) { // u 节点不属于 S 集合
            res = min(res, rec(S | (1 << u), u) + d[v][u]);
        }
    }
    dp[S][v] = res;
    return res;
}

void solve(void) {
    memset(dp, -1, sizeof(dp));
    printf("%d\n", rec(0, 0)); // 未访问任何点, 起点为0
}

int main(void) {
    n = 5;
    memset(d, 0x3f, sizeof(d));
    for (int i = 0; i < n; ++i) dp[i][i] = 0;
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