#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int INF = 0x7f7f7f7f;

// 必须从下往上dp, 否则会WA
int T;
int N, X, Y, MAX;
typedef struct Node {
    bool operator<(const Node& n2) const { return h < n2.h; } // 低的排在前面
    int l, r, h;
} Node;
Node plat[maxn];
int dp[maxn][2]; // dp[i][0]:从终点来到第i块左边的最短时间, dp[i][1]:从终点来到第i块右边的最短时间
int solve(void) {
    memset(dp, 0x7f, sizeof(dp));
    sort(plat + 1, plat + N + 1); // 起始位置高于所有平台
    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= N + 1; ++i) {
        int lj = -1, rj = -1;
        for (int j = i - 1; j >= 0 && plat[i].h - plat[j].h <= MAX && (lj == -1 || rj == -1); --j) { // 找到i下面第一块板子
            // i左边能跳下去的板子lj
            if (plat[i].l >= plat[j].l && plat[i].l <= plat[j].r && lj == -1) {
                lj = j;
            }
            // i右边能跳下去的板子rj
            if (plat[i].r >= plat[j].l && plat[i].r <= plat[j].r && rj == -1) {
                rj = j;
            }
        }
        if (lj == 0) dp[i][0] = plat[i].h; // 可以直达地面
        else if (lj != -1) dp[i][0] = min(dp[i][0], 
                min(dp[lj][0] + abs(plat[i].l - plat[lj].l) + plat[i].h - plat[lj].h,
                    dp[lj][1] + abs(plat[i].l - plat[lj].r) + plat[i].h - plat[lj].h));
        if (rj == 0) dp[i][1] = plat[i].h; // 可以直达地面
        else if (rj != -1) dp[i][1] = min(dp[i][1],
                min(dp[rj][0] + abs(plat[i].r - plat[rj].l) + plat[i].h - plat[rj].h,
                    dp[rj][1] + abs(plat[i].r - plat[rj].r) + plat[i].h - plat[rj].h));
    }
    return dp[N + 1][0];
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &N, &X, &Y, &MAX);
        for (int i = 1; i <= N; ++i) {
            scanf("%d%d%d", &plat[i].l, &plat[i].r, &plat[i].h);
        }
        plat[N + 1].l = plat[N + 1].r = X, plat[N + 1].h = Y; // 起点
        plat[0].l = -INF, plat[0].r = INF, plat[0].h = 0; // 终点
        printf("%d\n", solve());
    }
    return 0;
}