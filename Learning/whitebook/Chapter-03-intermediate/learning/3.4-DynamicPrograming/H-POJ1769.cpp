// ---------------------------------------------------------------------
// 题目描述:
// Maximizer 的输入为 n 个整数, 输出为他们的最大值.
// 这个装置由 m 个 Sorter 组成, 第 k 个 Sorter 的输入为第 k - 1 个 Sorter 的输出.
// 每个 Sorter 将第 sk 到 tk 个值进行排序后, 其余部分保持不变输出.
// 最后一个 Sorter 输出的第 n 个值就是 Maximizer 的输出.
// 从 Maximizer 去掉几个 Sorter 之后, Maximizer 仍有可能正常工作.
// 给定 Sorter 的序列, 求其中的最短的子序列(可以不连续)使得 Maximizer 仍能正常工作.
// 2 <= n <= 50000
// 1 <= m <= 500000
// 1 <= sk < tk <= n
// ---------------------------------------------------------------------
// 思路:
// 先考虑朴素的动态规划
// 不妨假设输入的第一个数是应该输出的最大值.
// dp[i][j] := 到第i个Sorter, 最大值被移动到第j个位置所需的最短子序列长度
// dp[0][1] = 0
// dp[0][j] = INF(j>1)
//              | dp[i][j] (ti != j)
// dp[i+1][j] = |
//              | min{dp[i][j], min{dp[i][j'] | si <= j' <= ti} + 1} (ti == j)
// 复杂度是O(nm), 显然会超时.
// 不妨先用滚动数组优化, 观察到只有 dp[i+1][ti] 会发生更新
// dp[j] := 最大值被移动到位置 j 位置所需要的最短子序列长度
// dp[1] = 0
// dp[j] = INF(j>1)
// dp[ti] = min{dp[ti], min{ dp[j'] | si <= j' <= ti} + 1}
// 这样对于每个 i 都只需更新一个值就可以了.
// 结合线段树维护, 就可以把时间复杂度降低为O(m log(n))
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 50010;
const int maxm = 500010;
const int INF = 0x3f3f3f3f;

// input
int n, m;
int s[maxm], t[maxm];

int dp[maxn + 1];

// ST
const int ST_SIZE = (1 << 18) - 1;
int stn, dat[ST_SIZE];

// 初始化RMQ线段树
void rmq_init(int x) {
    stn = 1;
    while (stn < x) stn *= 2;
    memset(dat, 0x3f, sizeof(dat));
}

// 把第k个值更新为a
void update(int k, int a) {
    k += stn - 1;
    dat[k] = a;
    while (k > 0) {
        k = (k - 1) / 2;
        dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
}

// 求[a, b)区间的最小值
int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INF;
    if (a <= l && r <= b) return dat[k];
    else {
        int v1 = query(a, b, k * 2 + 1, l, (l + r) / 2);
        int v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(v1, v2);
    }
}

void solve(void) {
    rmq_init(n); // 初始化线段树
    fill(dp, dp + n + 1, INF);
    dp[1] = 0;
    update(1, 0);
    for (int i = 0; i < m; ++i) {
        int v = min(dp[t[i]], query(s[i], t[i] + 1, 0, 0, stn) + 1);
        dp[t[i]] = v;
        update(t[i], v);
    }
    printf("%d\n", dp[n]);
}

int main(void) {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < m; ++i) scanf("%d%d", &s[i], &t[i]);
        solve();
    }
}