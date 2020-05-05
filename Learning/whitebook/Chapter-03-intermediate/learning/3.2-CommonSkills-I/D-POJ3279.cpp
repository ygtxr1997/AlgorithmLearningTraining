// ---------------------------------------------------------------------
// 题目描述:
// M * N 的方阵, 每个格子是黑色或者白色, 黑白可以互相反转.
// 并且每次反转一个格子的同时, 周围四个格子也会被反转.
// 求出把所有格子都反转成白色的最小步数, 如果不可能全部变成白色, 输出IMPOSSIBLE.
// ---------------------------------------------------------------------
// 思路:
// 典型的反转(开关)问题
// 1. 同一个格子最多只需要反转一次
// 2. 格子反转的次序不影响最终结果
// 3. 先考虑第一行, 一旦第一行的反转方式确定了,
//    那么第二行必须把第一行的剩余黑色反转成白色, 因此第二行的反转顺序也确定了.
//    也就是说, 第一行的反转方式决定了接下来每一行的反转方式.
//    依此类推直到最后一行, 如果最后一行反转后全为白色, 说明该方案可行;
//    否则该方案不可行, 继续枚举第一行的下一种反转方式.
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 17;
const int dx[5] = {-1, 0, 0, 0, 1};
const int dy[5] = {0, -1, 0, 1, 0};

int M, N; // M行, N列
int tile[maxn][maxn]; // 初始方阵

int opt[maxn][maxn]; // 保存最优解
int flip[maxn][maxn]; // 中间结果, 方便最后打印要反转的点

// 查询(x,y)的颜色
int get(int x, int y) {
    int c = tile[x][y];
    for (int d = 0; d < 5; d++) {
        int x2 = x + dx[d], y2 = y + dy[d];
        if (x2 >= 0 && x2 < M && y2 >= 0 && y2 < N) {
            c += flip[x2][y2];
        }
    }
    return c % 2;
}

// 给定第1行的反转情况, 求出对应的最小操作次数
// 如果无法反转成全白, 则返回-1
int calc(void) {
    // 求出从第二行开始的翻转方法
    for (int i = 1; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (get(i - 1, j) == 1) { // 上一行的同一列位置为黑色, 需要翻转
                flip[i][j] = 1;
            }
        }
    }

    // 判断最后一行是否全白
    for (int j = 0; j < N; ++j) {
        if (get(M - 1, j) == 1) {
            return -1; // 无解
        }
    }

    // 统计翻转次数
    int res = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            res += flip[i][j];
        }
    }
    return res;
}

void solve(void) {
    int res = -1;
    // 按照字典序尝试第一行的所有可能翻转方法
    for (int i = 0; i < (1 << N); ++i) {
        memset(flip, 0, sizeof(flip));
        for (int j = 0; j < N; ++j) {
            flip[0][N - j - 1] = (i >> j) & 1; // bit位为1则代表需要翻转
        }
        int num = calc();
        if (num >= 0 && (res < 0 || res > num)) {
            res = num;
            memcpy(opt, flip, sizeof(flip));
        }
    }

    if (res < 0) {
        printf("IMPOSSIBLE\n");
    } else {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d%c", opt[i][j], j + 1 == N ? '\n' : ' ');
            }
        }
    }
}

int main(void) {
    while (scanf("%d%d", &M, &N) != EOF) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &tile[i][j]);
            }
        }
        solve();
    }
    return 0;
}