// ---------------------------------------------------------------------
// 题目描述:
// 在平面直角坐标系上有 N 条首尾相连的线段, 开始时线段均与 y 轴重合, 所有的线段
// 都笔直连接指向上方.
// 有 C 条操作线段的指令, 指令 i 给出两个整数 Si 和 Ai, 效果是使得线段 Si 和
// 线段 Si+1 之间的角度变成 Ai 度. 角度指的是下面线段逆时针旋转到上面线段经过的角度.
// 按顺序执行这 C 条指令, 每条指令执行完后输出最上面的线段的末端坐标.
// 假设第一条线段的起点坐标为 (0, 0).
// 1 <= N, C <= 10000
// 1 <= Li <= 100
// 1 <= Si < N, 0 <= Ai <= 359
// ---------------------------------------------------------------------
// 思路:
// 线段树的变形题, 但在做此题之前先补充向量的数学知识.
// 设向量 V1 = (x1, y1), 与 x 轴正向夹角为 A,
// 将向量 V1 逆时针旋转 B 角度后得到向量 V2 = (x2, y2), V2 可以通过三角函数表示出来.
// 设 V1 长为 R,
// 则 x1 = R * cosA, y1 = R * sinA,
// 且 x2 = R * cos(A+B), y2 = R * sin(A+B),
// 根据三角函数展开式: cos(A+B)=cosAcosB-sinAsinB, sin(A+B)=sinAcosB+cosAsinB
//    x2 = R * (cosAcosB - sinAsinB)
//    y2 = R * (sinAcosB + cosAsinB)
// 代入 R = x1 / cosA, R = y1 / sinA,
//    x2 = x1 * cosB - y1 * sinB
//    y2 = x1 * sinB + y1 * cosB
// 这就是二维向量的逆时针旋转公式.
// 回到原题, 用线段树的每个节点表示一段连续的线段集合, 并且维护 2 个值:
// 1. 将线段集合的第一条线段转至垂直朝上后, 连续线段集合的第一条线段的起点指向最后一条线段的终点的向量.
// 2. (如果有儿子节点)两个儿子节点对应部分连接之后, 右儿子需要转动的角度.
// 也就是说, 如果树节点 i 代表的向量是 vxi, vyi, 角度是angi, 两个儿子节点分别是 chl 和 chr, 那么有,
// vxi = vxchl + (cos(angi)*vxchr - sin(angi)*vychr)
// vyi = vxchl + (sin(angi)*vxchr + cos(angi)*vychr)
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace::std;
const int maxn = 10010;
const int ST_SIZE = (1 << 15) - 1;
double PI = acos(-1.0);

// input
int N, C;
int L[maxn];
int S[maxn], A[maxn];

// 线段树
double vx[ST_SIZE], vy[ST_SIZE]; // 向量
double ang[ST_SIZE]; // 角度

// 为了查询角度的变化而保存的当前角度
double prv[maxn];

// 初始化线段树
// k:节点编号, l,r:节点对应区间[l,r)
void init(int k, int l, int r) {
    ang[k] = vx[k] = 0.0; // 初始时, 横坐标均为0, 角度均为0
    if (r - l == 1) { // 叶子
        vy[k] = L[l];
    } else { // 非叶子
        int chl = k * 2 + 1, chr = k * 2 + 2;
        init(chl, l, (l + r) / 2);
        init(chr, (l + r) / 2, r);
        vy[k] = vy[chl] + vy[chr];
    }
}

// 把S和S+1的角度变为a
// v:节点编号, l,r:节点对应区间[l,r)
void change(int s, double a, int v, int l, int r) {
    if (s <= l) return;
    else if (s < r) {
        int chl = v * 2 + 1, chr = v * 2 + 2;
        int m = (l + r) / 2;
        change(s, a, chl, l, m);
        change(s, a, chr, m, r);
        if (s <= m) ang[v] += a; // s在左半部分时, 右半部分才需要旋转

        double si = sin(ang[v]), co = cos(ang[v]);
        vx[v] = vx[chl] + (co * vx[chr] - si * vy[chr]);
        vy[v] = vy[chl] + (si * vx[chr] + co * vy[chr]);
    }
}

void solve(void) {
    // 初始化
    init(0, 0, N);
    for (int i = 1; i < N; ++i) prv[i] = PI;

    // 处理操作
    for (int i = 0; i < C; ++i) {
        int s = S[i];
        double a = A[i] / 360.0 * 2 * PI; // 角度转为弧度
        change(s, a - prv[s], 0, 0, N); // 旋转角 = a - prv[s]
        prv[s] = a;
        printf("%.2f %.2f\n", vx[0], vy[0]);
    }
}

int main(void) {
    while (scanf("%d%d", &N, &C) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &L[i]);
        for (int i = 0; i < C; ++i) scanf("%d %d", &S[i], &A[i]);
        solve();
    }
    return 0;
}