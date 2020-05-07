// ---------------------------------------------------------------------
// 题目描述:
// 一个旅行家计划马车旅行, 他所在的国家里有 m 个城市.
// 在城市之间有若干条道路相连, 通过马车可以到达另一个城市.
// 乘坐马车需要车票, 每用一张车票只可以通过一条道路, 车票上写有马的数量.
// 从一个城市到另一个城市花费的时间 = 城市之间的道路长度 / 马的数量.
// 旅行家一共有 n 张车票, 第 i 张车票上马的数量是 ti.
// 一张车票只能使用一次, 求从城市 a 到城市 b 的最短时间.
// 如果无法到达则输出 "Impossible".
// 1 <= n <= 8
// 2 <= m <= 30
// 1 <= a,b <= m (a!=b)
// 1 <= ti <= 10
// 1 <= 道路的长度 <= 100
// ---------------------------------------------------------------------
// 思路:
// 状态压缩dp
// 设状态"现在在城市v, 此时还剩的车票集合为S".
// 从这个状态出发, 使用一张车票 i∈S 移动到相邻城市, 就相当于来到了另一个状态
// "在城市u, 剩余车票集合为S-{i}".
// 把这个转移看成一条边, 那么边的花费 = d(v,u)/ti.
// 按照这个方法构图, 就可以用 dijkstra 算法求解了.
// 而 DAG 的最短路用 dp 也可以求解.
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 9;
const int maxm = 31;
const int INF = 0x3f3f3f3f;

// input
int n, m, p, a, b; // 票数, 城市数, 路数, 起点, 终点
int t[maxn];
int d[maxm][maxm]; // 邻接矩阵, -1表示没有边

// dp[S][v]:=来到城市v, 剩余车票集合为S, 的最小花费
double dp[1 << maxn][maxm];

void solve(void) {
    for (int i = 0; i < (1 << n); ++i) {
        fill(dp[i], dp[i] + m, INF); // 初始化不能用memset
    }
    dp[(1 << n) - 1][a - 1] = 0;
    double res = INF;
    for (int S = (1 << n) - 1; S >= 0; S--) { // 车票集合
        res = min(res, dp[S][b - 1]);
        for (int v = 0; v < m; ++v) { // 城市v
            for (int i = 0; i < n; ++i) { // 车票
                if (S >> i & 1) { // 集合S包含车票i
                    for (int u = 0; u < m; ++u) { // 城市u
                        if (d[v][u] >= 0) { // 存在路径
                            // 去掉第i张车票的状态
                            dp[S & ~(1 << i)][u] = 
                                min(dp[S & ~(1 << i)][u],
                                dp[S][v] + (double)d[v][u] / t[i]);
                        }
                    }
                }
            }
        }
    }
    if (res == INF) printf("Impossible\n");
    else printf("%.3f\n", res);
}

int main(void) {
    while (scanf("%d%d%d%d%d", &n, &m, &p, &a, &b) && n + m + p + a + b != 0) {
        memset(d, -1, sizeof(d));
        for (int i = 0; i < m; ++i) d[i][i] = 0;
        for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
        for (int i = 0; i < p; ++i) {
            int x, y, dxy;
            scanf("%d%d%d", &x, &y, &dxy);
            d[x - 1][y - 1] = d[y - 1][x - 1] = dxy; // 城市下标从0开始
        }
        solve();
    }
    return 0;
}